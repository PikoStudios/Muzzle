#include "core/Drawing.h"

void begin_drawing()
{
    rlClearScreenBuffers(); // may not be needed???
    BeginDrawing(); // Need to use raylib because we would need CORE which is not exposed
}
void end_drawing()
{
    // we need to use raylib EndDrawing because raylib handles the window so we need the buffers to be swapped by raylib
    EndDrawing();
}