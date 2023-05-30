#pragma once
#include "Loop.h"
#include "Error.h"
#include "callback.h"
#include "../backend.h"
#include "Batcher.h"
#include "../modern_pipeline/Shaders.h"

#ifndef MZ_DEFAULT_BATCH_SIZE
    #define MZ_DEFAULT_BATCH_SIZE 1000
#endif

#define MZ_APPLET_FLAG_NONE 1
#define MZ_APPLET_FLAG_DONT_INIT_BATCHER 2

typedef struct Applet
{
    int width, height;
    char* window_title;
    batcher batch;
    GLFWwindow* window_handle;
} Applet;
    
#ifdef __cplusplus
extern "C" {
#endif

/*
* StartApplet - Start a Applet
* @param self Pointer to Applet
*/
MZ_API void StartApplet(Applet* self);

/*
* InitializeApplet - Create an Applet
* @param WIDTH Width of Screen
* @param HEIGHT Height of Screen
* @param WINDOW_TITLE Title of the Window
* @param RESIZEABLE Toggle resizeability
* @param VSYNC Toggle VSync, If set to MUZZLE_FALSE Muzzle will try to use as much of the GPU and CPU that it can usep
* @return Applet
*/
MZ_API Applet InitializeApplet(const int WIDTH, const int HEIGHT, const char* WINDOW_TITLE, int RESIZEABLE, int VSYNC, uint32_t EXTRA_FLAGS);
#ifdef __cplusplus
}
#endif
