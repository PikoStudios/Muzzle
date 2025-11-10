#include "core/font.h"
#include "backend.h"
#include "core/logging.h"
#include "core/applet.h"
#include <math.h>

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

	unsigned char* temp_rescaling_buffer = MZ_CALLOC(MUZZLE_TEXT_SOURCE_FONT_SIZE * MUZZLE_TEXT_SOURCE_FONT_SIZE, sizeof(unsigned char));

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

		int glyph_width = (face->glyph->bitmap.width < MUZZLE_TEXT_SOURCE_FONT_SIZE) ? face->glyph->bitmap.width : MUZZLE_TEXT_SOURCE_FONT_SIZE;
		int glyph_height = (face->glyph->bitmap.rows < MUZZLE_TEXT_SOURCE_FONT_SIZE) ? face->glyph->bitmap.rows : MUZZLE_TEXT_SOURCE_FONT_SIZE;

		unsigned char* buffer = face->glyph->bitmap.buffer;

		// rescale glpyh
		
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
