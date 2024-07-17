#ifndef MUZZLE_PRIMITIVES_TEXT_H
#define MUZZLE_PRIMITIVES_TEXT_H

#include "../backend.h"
#include "core/applet.h"
#include "core/vector.h"
#include <stdint.h>

typedef struct mz_font_glyph
{
	GLuint texture_id;
	mz_vec2_i size;
	mz_vec2_i bearing;
	uint32_t advance;
} mz_font_glyph;

typedef struct mz_font
{
	mz_font_glyph* glyphs;
	uint32_t glyph_count;
} mz_font;

MZ_API mz_font mz_load_font(mz_applet* applet, const char* filepath);
MZ_API void mz_unload_font(mz_font* font);

#endif // MUZZLE_PRIMITIVES_TEXT_H
