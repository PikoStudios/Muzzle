#pragma once
#ifndef MUZZLE_USE_MODERN_RENDERER

#ifdef MUZZLE_DEPS
    #define FONTSTASH_IMPLEMENTATION
    #define GLFONTSTASH_IMPLEMENTATION
#endif


#include <stdio.h>					// malloc, free, fopen, fclose, ftell, fseek, fread
#include <string.h>					// memset
#include "../backend.h"
#include "../deps/fontstash/src/fontstash.h"
#include "../deps/fontstash/src/gl3corefontstash.h"
#include "Error.h"
#include "tint.h"
#include "vector.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef FONScontext font_manager;

typedef struct font
{
    int fn;
    FONScontext* context;
} font;

// Load Font
MZ_API font load_font(const char* filepath, const char* name);
MZ_API void unload_font(font font_used);


/*
 * WARNING
 * =======
 *
 * Loading fonts to a font manager is no longer supported in Muzzle.
 * If you still wish to use a font manager not created by the Muzzle `load_font` API Function
 * Simply dispose of the provided font manager, and pass a pointer to a new manager to the `context`
 * struct member.
 *
 * What ever pointer is set in the `context` struct member **will** be used in text drawing operations
 *
*/


// Draw Text
MZ_API void draw_text(font font_used, const char *text, float x, float y, float font_size, tint color_drawn);
MZ_API void draw_text_vec2(font font_used, const char *text, vec2 pos, float font_size, tint color_drawn);

MZ_API void draw_text_center(font font_used, const char* text, float x, float y, float font_size, tint color_drawn);
MZ_API void draw_text_center_vec2(font font_used, const char* text, vec2 pos, float font_size, tint color_drawn);

MZ_API void draw_blurred_text(font font_used, const char *text, float x, float y, float intensity, float font_size, tint color_drawn);
MZ_API void draw_shadow_text(font font_used, const char *text, float x, float y, tint shadow_color, float intensity, float font_size, tint color_drawn);

MZ_API void draw_blurred_text_vec2(font font_used, const char *text, vec2 position, float intensity, float font_size, tint color_drawn);
MZ_API void draw_shadow_text_vec2(font font_used, const char *text, vec2 position, tint shadow_color, float intensity, float font_size, tint color_drawn);

// Get Text Data
MZ_API int get_text_codepoint(const char* text, int* bytes_processed);
MZ_API vec2 get_text_size(font font_used, const char* text, float font_size);

#ifdef __cplusplus
}
#endif
#endif