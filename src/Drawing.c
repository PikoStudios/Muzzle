#include "core/Drawing.h"

void begin_drawing(tint color_drawn)
{
    rlClearColor((float)(color_drawn.r)/255,(float)(color_drawn.g)/255,(float)(color_drawn.b)/255,(float)(color_drawn.a)/255);
    rlClearScreenBuffers(); // may not be needed???
    BeginDrawing(); // Need to use raylib because we would need CORE which is not exposed
}
void end_drawing()
{
    // we need to use raylib EndDrawing because raylib handles the window so we need the buffers to be swapped by raylib
    EndDrawing();
}