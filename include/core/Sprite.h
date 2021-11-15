#pragma once
#include "../backend.h"
#ifdef MUZZLE_DEPS
    #define STB_IMAGE_IMPLEMENTATION
#endif
#include "../../deps/stb/stb_image.h"
#include "Error.h"
#include "tint.h"
#include "vector.h"
#include "../shapes/Rectangle.h"

struct _mz_sprite
{
    unsigned int sprite_id;
    int width,height;
};

/*
Muzzle Sprite
=============
unsigned int sprite_id
int width, height
*/
typedef struct _mz_sprite sprite;

#ifdef __cplusplus
extern "C" {
#endif


sprite load_sprite(const char *filepath);
sprite *load_sprite_ptr(const char *filepath);
void unload_sprite(sprite *data);
void draw_sprite(sprite *data, int x, int y, float scale, float rotation, tint color_drawn);
void draw_sprite_vec2(sprite *data, vec2 pos, float scale, float rotation, tint color_drawn);
void draw_sprite_portion(sprite* data, rectangle rec, vec2 pos, tint color_drawn);

#ifdef __cplusplus
}
#endif
