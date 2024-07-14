#include "backend.h"
#include "core/logging.h"
#include "core/sprite_renderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../deps/stb/stb_image.h"
#include "primitives/sprite.h"

mz_sprite mz_load_sprite(const char* filepath)
{
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

#ifdef MUZZLE_DEBUG_BUILD
	mz_log_status_formatted(LOG_STATUS_SUCCESS, "Loaded image '%s' into GPU", filepath);
#endif

	stbi_image_free(data);

	return (mz_sprite)
	{
		.width = w,
		.height = h,
		._id = id
	};
}

void mz_unload_sprite(mz_sprite* data)
{
	glDeleteTextures(1, &data->_id);
}

#define TINT_TO_VEC4(t) (mz_vec4){(float)(t.r),(float)(t.g),(float)(t.b), (float)(t.a)}
#define VERTEX(x,y,t,tcx,tcy,tid,tf,ro) (struct mz_sprite_vertex){(mz_vec2){x,y}, t, (mz_vec2){tcx, tcy}, tid, tf, ro}

void mz_draw_sprite(mz_applet* applet, mz_sprite* data, float x, float y, mz_tint tint)
{
	applet->render_order++;

	int texture_id = mz_sprite_renderer_push_texture(&applet->sprite_renderer, data->_id);

	if (texture_id == -1)
	{
		mz_sprite_renderer_flush(&applet->sprite_renderer, applet->width, applet->height, applet->render_order);
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
		mz_sprite_renderer_flush(&applet->sprite_renderer, applet->width, applet->height, applet->render_order);
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
