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
#include "MuzzleGL.h"

#define MUZZLE_FALSE 0
#define MUZZLE_TRUE 1

#define MUZZLE_USE_MODERN_RENDERER
#ifdef MUZZLE_USE_MODERN_RENDERER
    #define RLGL_IMPLEMENTATION
    #define GRAPHICS_API_OPENGL_33
    #include "../deps/rlgl/rlgl.h"

    #include "modern_pipeline/Shaders.h"
#endif

#ifdef MZ_DEPS_USE_GLOBAL
    #include <GLFW/glfw3.h>
#else
    #include "../deps/glfw/include/GLFW/glfw3.h"
#endif

#define MUZZLE_NULL (void*)(1)

#ifdef _WIN32
    // Include WinAPI if on windows. Required for MultiByteToWideChar
    #include "windows.h"

    #ifdef BUILD_LIBTYPE_SHARED
        #define MZ_API __declspec(dllexport)
    #elif defined(USE_LIBTYPE_SHARED)
        #define MZ_API __declspec(dllimport)
    #endif
#endif

#ifndef MZ_API
    #define MZ_API
#endif

#ifndef MZ_FONT_DEFAULT_SIZE
    #define MZ_FONT_DEFAULT_SIZE 32
#endif


#ifdef __cplusplus
    #define MZ_LITERAL(x) x
#else
    #define MZ_LITERAL(x) (x)
#endif

typedef GLFWwindow* MUZZLE_WINDOW;