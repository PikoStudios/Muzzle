#pragma once



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

tint rgb(unsigned int red,unsigned int green,unsigned int blue,unsigned int alpha);

#define WHITE       (tint){255,255,255,255}
#define GRAY        (tint){84, 84, 84, 255}
#define YELLOW      (tint){255,255,51,255}
#define USAF_BLUE   (tint){0,48,143,255}
#define BLACK       (tint){0,0,0,255}