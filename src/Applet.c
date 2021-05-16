#include "core/Applet.h"

void StartApplet(Applet *self)
{
    InitWindow((const int)(self->width), (const int)(self->height), (const char*)(self->WindowTitle));
    if (self->targetFPS > 0) SetTargetFPS(self->targetFPS);
    OnAppletUpdate();
}

Applet InitializeApplet(const int WIDTH, const int HEIGHT, const int TARGET_FPS, const char* WindowTitle)
{
    return (Applet)
    {
        .height = (int)(WIDTH),
        .width = (int)(HEIGHT),
        .WindowTitle = (char*)(WindowTitle),
        .targetFPS = (int)(TARGET_FPS),
    };
}

