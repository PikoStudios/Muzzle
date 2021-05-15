#include "core/Applet.h"

void StartApplet(Applet *self)
{
    if (CURRENT_GRAPHICS_BACKEND == BACKEND_RAYLIB)
    {
        InitWindow((const int)(self->width), (const int)(self->height), (const char*)(self->WindowTitle));
        if (self->targetFPS > 0) SetTargetFPS(self->targetFPS);
        OnAppletUpdate();
    }
    else if (CURRENT_GRAPHICS_BACKEND == BACKEND_RLGL)
    {
        rlglInit(self->width, self->height);
        OnAppletUpdate();
    }
}

Applet InitalizeApplet(const int WIDTH, const int HEIGHT, const int TARGET_FPS, const char* WindowTitle)
{
    Applet applet = {
        (int)(WIDTH), (int)(HEIGHT),
        (char*)(WindowTitle),
        (int)(TARGET_FPS)
        };
    return applet;
}

