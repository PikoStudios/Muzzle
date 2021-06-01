#pragma once
#include "../backend.h"
#include "../core/tint.h"
#include "../core/vector.h"


#ifdef MUZZLE_RAYLIB
/* 
Muzzle Rectangle
================
float X
float Y
float width
float height
*/
typedef Rectangle rectangle;

#else
/* 
Muzzle Rectangle
================
float X
float Y
float width
float height
*/
typedef struct rectangle
{
    float X;
    float Y;
    float width;
    float height;
} rectangle;
#endif

/* 
Muzzle draw_rectangle()
======================
Draw a rectangle to the screen
int x,y,width,height
tint color_drawn
*/
void draw_rectangle(int x, int y, int width, int height, tint color_drawn);
void draw_rectangle_rec(rectangle rec, tint color_drawn);
void draw_rectangle_vec2(vec2 pos, vec2 size, tint color_drawn);


