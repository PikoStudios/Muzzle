#include "backend.h"
#include "core/applet.h"
#include "core/logging.h"
#include "core/memory.h"
#include "core/sprite_renderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../deps/stb/stb_image.h"
#include "primitives/sprite.h"

mz_sprite mz_load_sprite(const char* filepath)
{
	MZ_TRACK_FUNCTION();
	
	int w, h, bpp;
	unsigned char* data = stbi_load(filepath, &w, &h, &bpp, 4);

	if (data == NULL)
	{
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Failed to load image '%s'", filepath);
	}

	GLuint id;
	glCreateTextures(GL_TEXTURE_2D, 1, &id);
	glTextureStorage2D(id, 1, GL_RGBA8, w, h);

	// Make texture repeat on axis, and add filter for pixel-perfect drawing
	glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureSubImage2D(id, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

#ifdef MUZZLE_DEBUG_BUILD
	mz_log_status_formatted(LOG_STATUS_SUCCESS, "Loaded image '%s' into GPU", filepath);
#endif

	return (mz_sprite)
	{
		.width = w,
		.height = h,
		._id = id
	};
}

MZ_API size_t mz_read_sprite_pixels(mz_sprite* data, unsigned char* out, size_t out_len)
{
	int size = data->width * data->height * 4;

	if (out == NULL)
	{
		goto retsize;
	}

#ifndef MUZZLE_SPRITE_DONT_FLIP_AFTER_READ
	unsigned char* buffer = MZ_MALLOC(size * sizeof(unsigned char));

	if (buffer == NULL)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Failed to allocate memory to read sprite pixels");
	}
#else
	unsigned char* buffer = out;
#endif

	glGetTextureImage(data->_id, 0, GL_RGBA, GL_UNSIGNED_BYTE, out_len, buffer);

#ifndef MUZZLE_SPRITE_DONT_FLIP_AFTER_READ
	unsigned char* tail = buffer + ((data->height - 1) * data->width * 4);

	for (int i = 0; i < data->height; i++)
	{
		if (i * data->width * 4 > out_len)
		{
			size = out_len;
			break;
		}

		memcpy(out + (i * data->width * 4), tail - (i * data->width * 4), data->width * 4);
	}

	MZ_FREE(buffer);
#endif

retsize:
	return size;
}

void mz_unload_sprite(mz_sprite* data)
{
	MZ_TRACK_FUNCTION();
	glDeleteTextures(1, &data->_id);
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))

mz_sprite_batch mz_load_sprite_batch(const char** filepaths, size_t size)
{
	MZ_TRACK_FUNCTION();

	if (filepaths == NULL || size == 0)
	{
		return (mz_sprite_batch){0};
	}

	int w1, h1;
	unsigned char* data1 = stbi_load(filepaths[0], &w1, &h1, NULL, 4);

	if (data1 == NULL)
	{
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Failed to load image '%s'", filepaths[0]);
	}

	GLuint id;
	glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &id);
	glTextureStorage3D(id, 1, GL_RGBA8, w1, h1, size);

	glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureSubImage3D(id, 0, 0, 0, 0, w1, h1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data1);

	stbi_image_free(data1);

	for (int i = 1; i < size; i++)
	{
		int w, h;
		unsigned char* data = stbi_load(filepaths[i], &w, &h, NULL, 4);

		w = MIN(w, w1);
		h = MIN(h, h1);

		if (data == NULL)
		{
			mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Failed to load image '%s'", filepaths[i]);
		}

		glTextureSubImage3D(id, 0, 0, 0, i, w, h, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	return (mz_sprite_batch)
	{
		.width = w1,
		.height = h1,
		.size = size,
		.id = id
	};
}

void mz_unload_sprite_batch(mz_sprite_batch* batch)
{
	glDeleteTextures(1, &batch->id);
	batch->id = 0;
	batch->width = 0;
	batch->height = 0;
	batch->size = 0;
}

void mz_bind_sprite_batch(mz_applet* applet, mz_sprite_batch* batch, uint8_t texture_unit)
{
	if (texture_unit >= applet->texture_units)
	{
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Cannot bind sprite batch to texture unit %d, exceeds amount of texture units supported on this GPU (%d)", texture_unit, applet->texture_units);
	}

	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(GL_TEXTURE_2D_ARRAY, batch->id);
}

#define TINT_TO_VEC4(t) (mz_vec4){(float)(t.r),(float)(t.g),(float)(t.b), (float)(t.a)}
#define VERTEX(x,y,t,tcx,tcy,tid,tf,ro) (struct mz_sprite_vertex){(mz_vec2){x,y}, t, (mz_vec2){tcx, tcy}, tid, tf, ro}

void mz_draw_sprite(mz_applet* applet, mz_sprite* data, float x, float y, mz_tint tint)
{
	MZ_TRACK_FUNCTION();

	applet->render_order++;

	int texture_id = mz_sprite_renderer_push_texture(&applet->sprite_renderer, data->_id);

	if (texture_id == -1)
	{
		mz_sprite_renderer_flush(&applet->sprite_renderer, applet->width, applet->height);
		texture_id = mz_sprite_renderer_push_texture(&applet->sprite_renderer, data->_id);

		MZ_ASSERT_DETAILED(texture_id > -1, "Texture Buffer should not be full");
	}

	mz_vec4 color = TINT_TO_VEC4(tint);
	struct mz_sprite_vertex v1 = VERTEX(x, y, color, 0, 0, texture_id, 1.0f, applet->render_order);
	struct mz_sprite_vertex v2 = VERTEX(x + data->width, y, color, 1, 0, texture_id, 1.0f, applet->render_order);
	struct mz_sprite_vertex v3 = VERTEX(x, y + data->height, color, 0, 1, texture_id, 1.0f, applet->render_order);
	struct mz_sprite_vertex v4 = VERTEX(x + data->width, y + data->height, color, 1, 1, texture_id, 1.0f, applet->render_order);

	if (mz_sprite_renderer_push_sprite(&applet->sprite_renderer, v1, v2, v3, v4) == MUZZLE_FALSE)
	{
		mz_sprite_renderer_flush(&applet->sprite_renderer, applet->width, applet->height);
#ifdef MUZZLE_DEBUG_BUILD
		MZ_ASSERT_DETAILED(mz_sprite_renderer_push_sprite(&applet->sprite_renderer, v1, v2, v3, v4) == MUZZLE_TRUE, "Quad renderer should not still be full")
#else
		mz_sprite_renderer_push_sprite(&applet->sprite_renderer, v1, v2, v3, v4);
#endif
	}
}

void mz_draw_sprite_vec2(mz_applet* applet, mz_sprite* data, mz_vec2 pos, mz_tint tint)
{
	mz_draw_sprite(applet, data, pos.x, pos.y, tint);
}
