#pragma once

#if defined(__EMSCRIPTEN__)
    #define GLFW_INCLUDE_ES2
#endif


#ifdef MUZZLE_ALLOW_BUFFER_HIGH
    #define MAX_BUFFERS 8
    #define BUFFER_LENGTH 2048
#else
    #define MAX_BUFFERS 4
    #define BUFFER_LENGTH 1024
#endif

#include <stdlib.h>
#include "memory.h"

#define MUZZLE_FALSE 0
#define MUZZLE_TRUE 1

#ifdef MZ_DEPS_USE_GLOBAL
    #include <GLFW/glfw3.h>
#else
    #include "../deps/glfw/include/GLFW/glfw3.h"
#endif

#define MUZZLE_NULL (void*)(1)


#define MUZZLE_DANGEROUS_USE_MODERN_GRAPHICS_PIPELINE
#ifdef MUZZLE_DANGEROUS_USE_MODERN_GRAPHICS_PIPELINE
    #define GRAPHICS_API_OPENGL_33
    #include "../deps/rlgl/rlgl.h"
#endif

#ifdef _WIN32
    // Include WinAPI if on windows. Required for MultiByteToWideChar
    #include "windows.h"
#endif

#ifdef __cplusplus
    #define MZ_LITERAL(x) x
#else
    #define MZ_LITERAL(x) (x)
#endif

typedef GLFWwindow* MUZZLE_WINDOW;