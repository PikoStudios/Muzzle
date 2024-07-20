#ifndef MUZZLE_CORE_FONT_H
#define MUZZLE_CORE_FONT_H

#include "../backend.h"
#include "vector.h"
#include <stdint.h>

// Doing this to fix circular dependency problem... :(
typedef struct mz_applet mz_applet;

typedef struct mz_font_glyph
{
	GLuint texture_idx;
	mz_vec2_i size;
	mz_vec2_i bearing;
	uint32_t advance;
	mz_boolean _loaded;
} mz_font_glyph;

typedef struct mz_font
{
	mz_font_glyph* glyphs;
	uint32_t glyph_count;
	GLuint texture_array_id; // TODO: not great for future proofing for multiple backends but thats a later me problem
} mz_font;

MZ_API mz_font mz_load_font(mz_applet* applet, const char* filepath);
MZ_API void mz_unload_font(mz_font* font);

#endif // MUZZLE_CORE_FONT_H
