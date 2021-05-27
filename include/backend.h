#pragma once

#if defined(__EMSCRIPTEN__)
    #define GLFW_INCLUDE_ES2
#endif


// everything includes this..

#ifdef MUZZLE_ALLOW_BUFFER_HIGH
    #define MAX_BUFFERS 8
    #define BUFFER_LENGTH 2048
#else
    #define MAX_BUFFERS 4
    #define BUFFER_LENGTH 1024
#endif

#include <stdbool.h>
#define GRAPHICS_API_OPENGL_33
#define RLGL_IMPLEMENTATION
#define RLGL_STANDALONE
#include "rlgl.h"

#include "../deps/glfw/include/GLFW/glfw3.h"

typedef GLFWwindow* MUZZLE_WINDOW;

#ifdef MUZZLE_ALLOW_TRACELOG
    #define RLGL_SUPPORT_TRACELOG
#endif
