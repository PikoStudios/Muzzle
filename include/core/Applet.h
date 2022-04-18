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
    
#ifdef __cplusplus
extern "C" {
#endif



/*
* StartApplet - Start a Applet
* @param self Pointer to Applet
*/
void StartApplet(Applet *self);

/*
* InitializeApplet - Create a new Applet
* @param WIDTH Width of Screen
* @param HEIGHT Height of Screen
* @param WINDOW_TITLE Title of the Window
* @param RESIZEABLE Ignore this, Just set to MUZZLE_FALSE
* @param VSYNC Toggle VSync, If set to MUZZLE_FALSE Muzzle will try to use as much of the GPU and CPU that it can use
* @return Applet
*/
Applet InitializeApplet(const int WIDTH, const int HEIGHT, const char* WINDOW_TITLE, int RESIZEABLE, int VSYNC);

#ifdef __cplusplus
}
#endif
