#ifndef MUZZLE_BACKEND_H
#define MUZZLE_BACKEND_H
// everything includes this..

#ifdef MUZZLE_ALLOW_BUFFER_HIGH
    #define MAX_BUFFERS 8
    #define BUFFER_LENGTH 2048
#else
    #define MAX_BUFFERS 4
    #define BUFFER_LENGTH 1024
#endif

// include backend code:
#define RLGL_IMPLEMENTATION
#define RLGL_STANDALONE
#ifdef MUZZLE_SUPPORT_RLGL_TRACELOG
    #define RLGL_SUPPORT_TRACELOG
#endif
#include "rlgl.h"

#if defined(__EMSCRIPTEN__)
    #define GLFW_INCLUDE_ES2
#endif

#include "../deps/glfw/include/GLFW/glfw3.h"

#endif