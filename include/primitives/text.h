#ifndef MUZZLE_PRIMITIVES_TEXT_H
#define MUZZLE_PRIMITIVES_TEXT_H

#include "../backend.h"
#include "core/applet.h"
#include "core/font.h"
#include "core/text_renderer.h"
#include "core/tint.h"
#include "core/vector.h"
#include <stdint.h>

MZ_API void mz_draw_text(mz_applet* applet, const char* text, float x, float y, float font_size, mz_font* font, mz_tint tint);
MZ_API void mz_draw_text_vec2(mz_applet* applet, const char* text, mz_vec2 position, float font_size, mz_font* font, mz_tint tint);
MZ_API void mz_draw_text_vec3(mz_applet* applet, const char* text, mz_vec3 position_and_font_size, mz_font* font, mz_tint tint);

// NOTE: This function does not produce perfectly accurate dimensions. This needs to be fixed
MZ_API mz_vec2 mz_measure_text(mz_applet* applet, const char* text, float font_size, mz_font* font);

#endif // MUZZLE_PRIMITIVES_TEXT_H
