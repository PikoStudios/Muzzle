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


typedef enum GRAPHICS_BACKEND
{
    BACKEND_RAYLIB,
    BACKEND_RLGL,
    BACKEND_SDL2,
} GRAPHICS_BACKEND;


// Graphics Backend
GRAPHICS_BACKEND CURRENT_GRAPHICS_BACKEND = BACKEND_RLGL;

#include "rlgl.h"
// Was having some issues with raylib's include guards.. So i created another include gaurd for it
#ifndef MUZZLE_BACKEND_RAYLIB_H
#define MUZZLE_BACKEND_RAYLIB_H
    #include "raylib.h"
#endif

#ifdef MUZZLE_RAYLIB
    CURRENT_GRAPHICS_BACKEND = BACKEND_RAYLIB;
#endif
//#ifdef MUZZLE_SDL2
//    CURRENT_GRAPHICS_BACKEND = BACKEND_SDL2;
//#endif

//#ifdef MUZZLE_MINIGFX
//    exit(-1);
//#endif

#endif