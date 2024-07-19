#include "primitives/text.h"
#include "core/font.h"
#include "core/logging.h"

mz_font mz_load_font(mz_applet* applet, const char* filepath, int max_font_size)
{
	mz_font font = (mz_font){0};
	FT_Face face = NULL;

	if (FT_New_Face(applet->font_library, filepath, 0, &face) != 0)
	{
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Could not load font '%s'", filepath);
	}

	FT_Set_Pixel_Sizes(face, 0, (max_font_size > 0) ? max_font_size : 64);

	font.glyph_count = face->num_glyphs;
	font.glyphs = MZ_CALLOC(font.glyph_count, sizeof(mz_font_glyph));

	if (font.glyphs == NULL)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Could not allocate memory for glyphs");
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	for (int i = 0; i < font.glyph_count; i++)
	{
		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
		{
			mz_log_status_formatted(LOG_STATUS_ERROR, "Failed to load glyph #%d from '%s'", i, filepath);
			continue;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &font.glyphs[i].texture_id);
		glTextureStorage2D(font.glyphs[i].texture_id, 1, GL_R8, face->glyph->bitmap.width, face->glyph->bitmap.rows);

		glTextureParameteri(font.glyphs[i].texture_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(font.glyphs[i].texture_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(font.glyphs[i].texture_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(font.glyphs[i].texture_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(
		        font.glyphs[i].texture_id,
		        0,
		        0,
		        0,
		        face->glyph->bitmap.width,
		        face->glyph->bitmap.rows,
		        GL_RED,
		        GL_UNSIGNED_BYTE,
		        face->glyph->bitmap.buffer
		);

		font.glyphs[i].size = (mz_vec2_i){face->glyph->bitmap.width, face->glyph->bitmap.rows};
		font.glyphs[i].bearing = (mz_vec2_i){face->glyph->bitmap_left, face->glyph->bitmap_top};
		font.glyphs[i].advance = face->glyph->advance.x;
	}

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	FT_Done_Face(face);
	
	return font;
}

void mz_unload_font(mz_font* font)
{
	MZ_FREE(font->glyphs);
	font->glyph_count = 0;
}
