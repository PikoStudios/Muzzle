#pragma once
#include "Loop.h"
#include "Error.h"
#include "callback.h"
#include "../backend.h"


typedef struct Applet
{
    int width, height;
    char* WindowTitle;
    GLFWwindow *window_handle;
} Applet;

void StartApplet(Applet *self);

Applet InitializeApplet(const int WIDTH, const int HEIGHT, const char* WINDOW_TITLE, int RESIZEABLE, int VSYNC);