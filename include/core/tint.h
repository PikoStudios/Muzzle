#pragma once
#include "error.h"
#include "../backend.h"

#ifdef __cplusplus
    #define RGBA(r,g,b,a) tint{r,g,b,a}
#else
    #define RGBA(r,g,b,a) (tint){r,g,b,a}
#endif


#ifdef __cplusplus
extern "C" {
#endif


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

#define WHITE      MZ_LITERAL(tint){255,255,255,255}
#define GRAY       MZ_LITERAL(tint){84, 84, 84, 255}
#define RED        MZ_LITERAL(tint){255,50,100,255}
#define ORANGE     MZ_LITERAL(tint){255,153,51,255}
#define GREEN      MZ_LITERAL(tint){102,255,102,255}
#define BLUE       MZ_LITERAL(tint){0,128,255,255}
#define PURPLE     MZ_LITERAL(tint){178,102,255,255}
#define PINK       MZ_LITERAL(tint){255,204,255,255}
#define MAGENTA    MZ_LITERAL(tint){255,102,255,255}
#define YELLOW     MZ_LITERAL(tint){255,255,51,255}
#define USAF_BLUE  MZ_LITERAL(tint){0,48,143,255}
#define BLACK      MZ_LITERAL(tint){0,0,0,255}


#ifdef __cplusplus
}
#endif
