#pragma once
#ifdef MUZZLE_DEPS
    #define FONTSTASH_IMPLEMENTATION
    #define GLFONTSTASH_IMPLEMENTATION
#endif


#include <stdio.h>					// malloc, free, fopen, fclose, ftell, fseek, fread
#include <string.h>					// memset
#include "../deps/fontstash/fontstash.h"
#include "../backend.h"
#include "../deps/fontstash/glfontstash.h"
#include "Error.h"
#include "tint.h"
#include "vector.h"

typedef FONScontext font_manager;

typedef int font;

font load_font(const char* filepath, font_manager* manager, const char* name);
void draw_text(font font_used, const char *text, float x, float y, float font_size, tint color_drawn, font_manager* manager);
void draw_text_vec2(font font_used, const char *text, vec2 pos, float font_size, tint color_drawn, font_manager* manager);