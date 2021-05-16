#pragma once

#ifdef MUZZLE_RAYLIB
/*
Muzzle tint (Color, RGBA)
===================
Raylib Backend
-----------------
unsigned char r,g,b,a
*/
typedef Color tint;
#else
/*
Muzzle tint (Color, RGBA)
===================
RLGL Backend
---------------
unsigned int r,g,b,a
*/
typedef struct tint
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;
} tint;
#endif


