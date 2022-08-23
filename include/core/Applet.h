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
MZ_API void StartApplet(Applet *self);

/*
* initialize_applet_pro - Create a new Applet with more options, meant for internal-use but it is safe to use
* @param WIDTH Width of Screen
* @param HEIGHT Height of Screen
* @param WINDOW_TITLE Title of the Window
* @param RESIZEABLE Toggle resizeability
* @param VSYNC Toggle VSync, If set to MUZZLE_FALSE Muzzle will try to use as much of the GPU and CPU that it can usep
* @param PIPELINE Which pipeline to create the Applet with. `0` - Legacy, `1` - Modern
* @return Applet
*/
MZ_API Applet initialize_applet_pro(const int WIDTH, const int HEIGHT, const char* WINDOW_TITLE, int RESIZEABLE, int VSYNC, int PIPELINE);

/*
* InitializeApplet - Create a new Applet
* @param WIDTH Width of Screen
* @param HEIGHT Height of Screen
* @param WINDOW_TITLE Title of the Window
* @param RESIZEABLE Toggle resizeability
* @param VSYNC Toggle VSync, If set to MUZZLE_FALSE Muzzle will try to use as much of the GPU and CPU that it can use
* @return Applet
*/
MZ_API Applet InitializeApplet(const int WIDTH, const int HEIGHT, const char* WINDOW_TITLE, int RESIZEABLE, int VSYNC);

/*
* InitializeAppletModern - Create a new Applet using the modern pipeline
* @param WIDTH Width of Screen
* @param HEIGHT Height of Screen
* @param WINDOW_TITLE Title of the Window
* @param RESIZEABLE Toggle resizeability
* @param VSYNC Toggle VSync, If set to MUZZLE_FALSE Muzzle will try to use as much of the GPU and CPU that it can use
* @return Applet
*/
MZ_API Applet InitializeAppletModern(const int WIDTH, const int HEIGHT, const char* WINDOW_TITLE, int RESIZEABLE, int VSYNC);

#ifdef __cplusplus
}
#endif
