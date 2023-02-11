#include "core/Animation.h"

animation load_animation(const char** locations, int size, vec2 position)
{
    sprite** sprites = malloc(sizeof(sprite*) * size);

    if (sprites == NULL)
    {
        log_status(STATUS_FATAL_ERROR, "Failed to Allocate Enough Memory for Sprites :: Point of Failure\n\tMUZZLE::ANIMATION::LOAD_ANIMATION::SPRITES::MALLOC");
    }
    for (int i = 0; i <= size; i++)
    {
        *sprites[i] = load_sprite(locations[i]);
    }

    return (animation)
    {
        .spr = sprites,
        .position = position,
        .frames = size,
        .current_frame = 0
    };
    
}
void play_animation(animation* data, long target_fps, float scale, float rotation, tint color_drawn)
{
    for (;data->current_frame <= data->frames; data->current_frame++)
    {
        draw_sprite_vec2(data->spr[data->current_frame], data->position, scale, rotation, color_drawn);
    }
    data->current_frame = 0;
}

void unload_animation(animation* data)
{
    for (int i = 0; i <= data->frames; i++)
    {
        free(data->spr[i]);
    }

    free(data->spr);
}