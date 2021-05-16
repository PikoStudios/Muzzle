#include "core/Drawing.h"

void begin_drawing()
{
#ifdef MUZZLE_RAYLIB
    BeginDrawing();
#else
    rlClearScreenBuffers();
    rlLoadIdentity();
#endif
}
void end_drawing()
{
    // we need to use raylib EndDrawing because raylib handles the window so we need the buffers to be swapped by raylib
    EndDrawing();
}