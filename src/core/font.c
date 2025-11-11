#include "core/font.h"
#include "backend.h"
#include "core/logging.h"
#include "core/applet.h"
#include "core/vector.h"
#include <math.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#ifndef MUZZLE_TEXT_DONT_RESCALE_LARGE_GLYPHS
// Rescale bitmap using Area Average
static inline void rescale_bitmap(unsigned char* src, int src_width, int src_height, unsigned char* out, int out_width, int out_height)
{
	mz_vec2 scale = (mz_vec2){(float)(src_width) / out_width, (float)(src_height) / out_height};

	for (int y = 0; y < out_height; y++)
	{
		for (int x = 0; x < out_width; x++)
		{
			float src_start_x = x * scale.x;
			float src_start_y = y * scale.y;
			float src_end_x = (x + 1) * scale.x;
			float src_end_y = (y + 1) * scale.y;

			int sum_color = 0;
			int pixel_count = 0;

			for (int src_y = (int)(src_start_y); y < src_end_y; y++)
			{
				for (int src_x = (int)(src_start_x); x < src_end_x; x++)
				{
					mz_vec2 overlap = (mz_vec2)
					{
						MIN(src_x + 1, src_end_x) - MAX(src_x, src_start_x),
						MIN(src_y + 1, src_end_y) - MAX(src_y, src_end_y)
					};

					float overlap_area = overlap.x * overlap.y;
					sum_color += src[src_y * src_width + src_x] * overlap_area;
					pixel_count += overlap_area;
				}
			}

			if (pixel_count > 0)
			{
				out[y * src_width + x] = sum_color / pixel_count;
			}
		}
	}
}
#endif

mz_font mz_load_font(mz_applet* applet, const char* filepath)
{
	MZ_TRACK_FUNCTION();

	mz_font font = (mz_font){0};
	FT_Face face = NULL;

	if (FT_New_Face(applet->font_library, filepath, 0, &face) != 0)
	{
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Could not load font '%s'", filepath);
	}

	if (FT_Set_Pixel_Sizes(face, MUZZLE_TEXT_SOURCE_FONT_SIZE, MUZZLE_TEXT_SOURCE_FONT_SIZE) != 0)
	{
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Could not set pixel sizes");
	}

	font.glyph_count = face->num_glyphs;
	font.glyphs = MZ_CALLOC(font.glyph_count, sizeof(mz_font_glyph));

	if (font.glyphs == NULL)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Could not allocate memory for glyphs");
	}

	int max_glyphs = font.glyph_count < 256 ? font.glyph_count : 256;

#if defined(MUZZLE_TEXT_AVOID_LOG2_OPTIMIZATION) || ((MUZZLE_TEXT_SOURCE_FONT_SIZE & (MUZZLE_TEXT_SOURCE_FONT_SIZE - 1)) != 0) // If source font size is not a power of two
	int levels = 1 + (int)floorf(log2f(MUZZLE_TEXT_SOURCE_FONT_SIZE));
#else
	int levels = 1 + (31 - __builtin_clz(MUZZLE_TEXT_SOURCE_FONT_SIZE));
#endif
	
	glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &font.texture_array_id);
	glTextureStorage3D(font.texture_array_id, levels, GL_R8, MUZZLE_TEXT_SOURCE_FONT_SIZE, MUZZLE_TEXT_SOURCE_FONT_SIZE, 256 /*font.glyph_count*/);
	
	glTextureParameteri(font.texture_array_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(font.texture_array_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(font.texture_array_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(font.texture_array_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	FT_Select_Charmap(face, FT_ENCODING_UNICODE);

#ifndef MUZZLE_TEXT_DONT_RESCALE_LARGE_GLYPHS
	unsigned char* temp_rescaling_buffer = MZ_CALLOC(MUZZLE_TEXT_SOURCE_FONT_SIZE * MUZZLE_TEXT_SOURCE_FONT_SIZE, sizeof(unsigned char));
#endif

	if (temp_rescaling_buffer == NULL)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Could not allocate memory for glyph rescaling buffer");
	}

	for (int i = 0; i < max_glyphs; i++)
	{
		if (FT_Get_Char_Index(face, i) == 0 || FT_Load_Char(face, i, FT_LOAD_RENDER))
		{
			mz_log_status_formatted(LOG_STATUS_ERROR, "Failed to load glyph #%d from '%s'", i, filepath);
			font.glyphs[i]._loaded = MUZZLE_FALSE;
			continue;
		}
#ifndef MUZZLE_TEXT_DONT_RESCALE_LARGE_GLYPHS
		unsigned char* buffer = face->glyph->bitmap.buffer;
#else
	// no need to store it in a variable, let's just make it a macro in this scenario
	#define buffer face->glyph->bitmap.buffer
#endif

#ifdef MUZZLE_TEXT_DONT_RESCALE_LARGE_GLYPHS
		int glyph_width = MIN(face->glyph->bitmap.width, MUZZLE_TEXT_SOURCE_FONT_SIZE);
		int glyph_height = MIN(face->glyph->bitmap.rows, MUZZLE_TEXT_SOURCE_FONT_SIZE);
#else
		int glyph_width = face->glyph->bitmap.width;
		int glyph_height = face->glyph->bitmap.rows;

		const mz_boolean width_exceeds = (face->glyph->bitmap.width > MUZZLE_TEXT_SOURCE_FONT_SIZE);
		const mz_boolean height_exceeds = (face->glyph->bitmap.rows > MUZZLE_TEXT_SOURCE_FONT_SIZE);

		if (width_exceeds || height_exceeds)
		{
			glyph_width = (width_exceeds) ? MUZZLE_TEXT_SOURCE_FONT_SIZE : glyph_width;
			glyph_height = (height_exceeds) ? MUZZLE_TEXT_SOURCE_FONT_SIZE : glyph_height;

			buffer = temp_rescaling_buffer;
			rescale_bitmap(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, buffer, glyph_width, glyph_height);
		}
#endif

		glTextureSubImage3D(
		        font.texture_array_id,
		        0,
		        0,
		        0,
		        i,
		        glyph_width,
		        glyph_height,
		        1,
		        GL_RED,
		        GL_UNSIGNED_BYTE,
		        buffer
		);

		font.glyphs[i].texture_idx = i;
		font.glyphs[i].size = (mz_vec2_i){face->glyph->bitmap.width, face->glyph->bitmap.rows};
		font.glyphs[i].bearing = (mz_vec2_i){face->glyph->bitmap_left, face->glyph->bitmap_top};
		font.glyphs[i].advance = face->glyph->advance.x;
		font.glyphs[i]._loaded = MUZZLE_TRUE;
	}

	glPixelStorei(GL_PACK_ALIGNMENT, 4);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glGenerateTextureMipmap(font.texture_array_id);

	FT_Done_Face(face);
	MZ_FREE(temp_rescaling_buffer);
	
	return font;
}

void mz_unload_font(mz_font* font)
{
	MZ_TRACK_FUNCTION();

	glDeleteTextures(1, &font->texture_array_id);
	MZ_FREE(font->glyphs);
	font->glyph_count = 0;
}
