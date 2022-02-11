#pragma once
#include "Loop.h"
#include "Error.h"
#include "callback.h"
#include "../backend.h"

typedef struct Applet
{
    int width, height;
#ifndef MUZZLE_DANGEROUS_NEW_APPLET_MEMBER_NAMES
    char* WindowTitle;
    GLFWwindow *window_handle;
#else
#error "Undefine \"MUZZLE_DANGEROUS_NEW_APPLET_MEMBER_NAMES\" due to new applet member names not being supported by Muzzle API"
    char* title;
    GLFWwindow *handle;
#endif
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
