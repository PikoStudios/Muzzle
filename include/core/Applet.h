#pragma once
#include "Loop.h"
#include "../backend.h"
#define DISABLE_VSYNC 0


typedef struct Applet
{
    int width, height;
    char* WindowTitle;
    int targetFPS;
} Applet;

void StartApplet(Applet *self);

Applet InitializeApplet(const int WIDTH, const int HEIGHT, const int TARGET_FPS, const char* WindowTitle);