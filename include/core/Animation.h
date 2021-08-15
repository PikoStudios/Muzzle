#pragma once
#include "../backend.h"
#include "Sprite.h"
#include "vector.h"
#include "Error.h"
#include "tint.h"
#include "time.h"

typedef struct animation
{
    sprite** spr;
    int frames;
    int current_frame;
    vec2 position;
} animation;

/*
* load_animation - Creates a animation struct
* @param locations A array of filepaths to the sprites
* @param size The amount of sprites [offset -1] 10 sprites :: size is 9
* @return A animation struct
*/
animation load_animation(const char** locations, int size, vec2 position);
/*
* play_animation - Plays a animation
* @param data A pointer to a animation struct
* @param target_fps Target FPS to be drawn
* @param scale Scale of sprites
* @param rotation rotation of sprites
* @param color_drawn Color drawn over sprite [White for no extra color]
* @return Nothing
*/
void play_animation(animation* data, long target_fps, float scale, float rotation, tint color_drawn);
/*
* unload_animation - Unloads a Animation
* @param data A pointer to a animation struct
* @return Nothing
*/
void unload_animation(animation* data);