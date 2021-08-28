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
static int __fons_initialized = 0;

static char __char_f_buffer[BUFFER_LENGTH];

typedef struct font
{
    int fn;
    FONScontext* context;
} font;

// Load Font
font load_font(const char* filepath, const char* name);
// Load Font to a Font Manager
font load_font_fs(const char* filepath, font_manager* manager, const char* name);

// Draw Text
void draw_text(font font_used, const char *text, float x, float y, float font_size, tint color_drawn);
void draw_text_vec2(font font_used, const char *text, vec2 pos, float font_size, tint color_drawn);

const char char_f(const char* text);

const char get_engine_char_f_buffer();

void draw_text_fs(font font_used, const char *text, float x, float y, float font_size, tint color_drawn, font_manager* manager);
void draw_text_vec2_fs(font font_used, const char *text, vec2 pos, float font_size, tint color_drawn, font_manager* manager);