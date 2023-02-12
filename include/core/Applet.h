#pragma once
#include "Loop.h"
#include "Error.h"
#include "callback.h"
#include "../backend.h"
#include "Batcher.h"
#include "../modern_pipeline/Shaders.h"

#ifndef MZ_BATCHER_SIZE
    #define MZ_BATCHER_SIZE 1000
#endif

typedef struct Applet
{
    int width, height;
    char* window_title;
    batcher_array rect_batchers;
    GLFWwindow* window_handle;
} Applet;
    
#ifdef __cplusplus
extern "C" {
#endif

/*
* __append_batchers - Internal function to append batcher array
* @param type Batcher Type
*/
MZ_API void __append_batchers(Applet* applet, int type);

/*
* set_global_shader - Set the global shader
* @param program Shader Program
*/
MZ_API void set_global_shader(Applet* applet, shader_program program);

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
MZ_API Applet InitializeApplet(const int WIDTH, const int HEIGHT, const char* WINDOW_TITLE, int RESIZEABLE, int VSYNC);
#ifdef __cplusplus
}
#endif
