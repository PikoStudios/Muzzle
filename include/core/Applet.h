#pragma once
#include "Loop.h"
#include "Error.h"
#include "callback.h"
#include "../backend.h"

#ifdef MUZZLE_DANGEROUS_USE_MODERN_GRAPHICS_PIPELINE
    #include "../modern_pipeline/Renderer.h"
#endif

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

#ifdef MUZZLE_DANGEROUS_USE_MODERN_GRAPHICS_PIPELINE
#warning "New Modern Graphics Pipeline is very unstable and not completed and/or usable yet"
    renderer* renderer;
#endif
} Applet;

#ifdef __cplusplus
extern "C" {
#endif


#ifdef MUZZLE_DANGEROUS_USE_MODERN_GRAPHICS_PIPELINE

/*
* set_main_renderer - Set main renderer
* @param self Pointer to applet
* @param renderer Pointer to Renderer
*/

static inline void set_main_renderer(Applet* self, renderer* renderer);

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
