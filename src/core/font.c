#include "core/font.h"
#include "backend.h"
#include "core/logging.h"
#include "core/applet.h"

mz_font mz_load_font(mz_applet* applet, const char* filepath)
{
	MZ_TRACK_FUNCTION();

	mz_font font = (mz_font){0};
	FT_Face face = NULL;

	if (FT_New_Face(applet->font_library, filepath, 0, &face) != 0)
	{
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Could not load font '%s'", filepath);
	}

	FT_Set_Pixel_Sizes(face, MUZZLE_TEXT_SOURCE_FONT_SIZE, MUZZLE_TEXT_SOURCE_FONT_SIZE);

	font.glyph_count = face->num_glyphs;
	font.glyphs = MZ_CALLOC(font.glyph_count, sizeof(mz_font_glyph));

	if (font.glyphs == NULL)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Could not allocate memory for glyphs");
	}
	
	glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &font.texture_array_id);
	glTextureStorage3D(font.texture_array_id, 1, GL_R8, MUZZLE_TEXT_SOURCE_FONT_SIZE, MUZZLE_TEXT_SOURCE_FONT_SIZE, 256 /*font.glyph_count*/);
	
	glTextureParameteri(font.texture_array_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(font.texture_array_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(font.texture_array_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(font.texture_array_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// TODO: i < font.glyph_count to load unicode characters
	for (int i = 0; i < 256; i++)
	{
		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
		{
			mz_log_status_formatted(LOG_STATUS_ERROR, "Failed to load glyph #%d from '%s'", i, filepath);
			font.glyphs[i]._loaded = MUZZLE_FALSE;
			continue;
		}

		glTextureSubImage3D(
		        font.texture_array_id,
		        0,
		        0,
		        0,
		        i,
		        face->glyph->bitmap.width,
		        face->glyph->bitmap.rows,
		        1,
		        GL_RED,
		        GL_UNSIGNED_BYTE,
		        face->glyph->bitmap.buffer
		        
		);

		font.glyphs[i].texture_idx = i;
		font.glyphs[i].size = (mz_vec2_i){face->glyph->bitmap.width, face->glyph->bitmap.rows};
		font.glyphs[i].bearing = (mz_vec2_i){face->glyph->bitmap_left, face->glyph->bitmap_top};
		font.glyphs[i].advance = face->glyph->advance.x;
		font.glyphs[i]._loaded = MUZZLE_TRUE;
	}

	glPixelStorei(GL_PACK_ALIGNMENT, 4);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	FT_Done_Face(face);
	
	return font;
}

void mz_unload_font(mz_font* font)
{
	MZ_TRACK_FUNCTION();

	glDeleteTextures(1, &font->texture_array_id);
	MZ_FREE(font->glyphs);
	font->glyph_count = 0;
}
