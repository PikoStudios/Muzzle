#pragma once
#include "error.h"

#define RGBA(r,g,b,a) (tint){r,g,b,a}


/*
Muzzle tint (Color, RGBA)
===================
unsigned int r,g,b,a
*/
typedef struct tint
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;
} tint;

tint hex_to_rgb(unsigned int hex[6], unsigned int alpha);

#define WHITE      (tint){255,255,255,255}
#define GRAY       (tint){84, 84, 84, 255}
#define RED        (tint){255,50,100,255}
#define ORANGE     (tint){255,153,51,255}
#define GREEN      (tint){102,255,102,255}
#define BLUE       (tint){0,128,255,255}
#define PURPLE     (tint){178,102,255,255}
#define PINK       (tint){255,204,255,255}
#define MAGENTA    (tint){255,102,255,255}
#define YELLOW     (tint){255,255,51,255}
#define USAF_BLUE  (tint){0,48,143,255}
#define BLACK      (tint){0,0,0,255}