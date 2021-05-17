#include "core/Drawing.h"

void begin_drawing(tint color_drawn)
{
    //rlLoadIdentity();
    BeginDrawing(); // Need to use raylib because we would need CORE which is not exposed
}
void end_drawing()
{
    // we need to use raylib EndDrawing because raylib handles the window so we need the buffers to be swapped by raylib
    EndDrawing();
}

void clear_screen(tint color_drawn)
{
    float r = (float)(color_drawn.r) / 255;
    float g = (float)(color_drawn.g) / 255;
    float b = (float)(color_drawn.b) / 255;
    float a = (float)(color_drawn.a) / 255;

    rlClearColor(r, g, b, a);
    rlClearScreenBuffers();
}