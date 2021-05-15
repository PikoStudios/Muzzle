#pragma once

typedef enum GRAPHICS_BACKEND
{
    BACKEND_RAYLIB,
    BACKEND_RLGL,
    BACKEND_SDL2,
} GRAPHICS_BACKEND;


// Graphics Backend
GRAPHICS_BACKEND CURRENT_GRAPHICS_BACKEND = BACKEND_RAYLIB;
// Include all the Backends
#include "rlgl.h"
#include "raylib.h"
#ifdef MUZZLE_RLGL
    CURRENT_GRAPHICS_BACKEND = BACKEND_RLGL;
#endif
#ifdef MUZZLE_SDL2
    CURRENT_GRAPHICS_BACKEND = BACKEND_SDL2;
#endif

//#ifdef MUZZLE_MINIGFX
//    exit(-1);
//#endif
