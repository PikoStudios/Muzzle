#pragma once
// everything includes this..

#ifdef MUZZLE_ALLOW_BUFFER_HIGH
    #define MAX_BUFFERS 8
    #define BUFFER_LENGTH 2048
#else
    #define MAX_BUFFERS 4
    #define BUFFER_LENGTH 1024
#endif

// Implement RLGL
#define RLGL_IMPLEMENTATION
typedef enum GRAPHICS_BACKEND
{
    BACKEND_RAYLIB,
    BACKEND_RLGL,
    BACKEND_SDL2,
} GRAPHICS_BACKEND;


// Graphics Backend
GRAPHICS_BACKEND CURRENT_GRAPHICS_BACKEND = BACKEND_RLGL;
// Include all the Backends
#include "rlgl.h"
#include "raylib.h"
#ifdef MUZZLE_RAYLIB
    CURRENT_GRAPHICS_BACKEND = BACKEND_RAYLIB;
#endif
//#ifdef MUZZLE_SDL2
//    CURRENT_GRAPHICS_BACKEND = BACKEND_SDL2;
//#endif

//#ifdef MUZZLE_MINIGFX
//    exit(-1);
//#endif
