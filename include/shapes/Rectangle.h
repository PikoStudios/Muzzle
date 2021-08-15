#pragma once
#include "../backend.h"
#include "../core/tint.h"
#include "../core/vector.h"

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
    float x;
    float y;
    float width;
    float height;
} rectangle;

/* 
Muzzle draw_rectangle()
======================
Draw a rectangle to the screen
int x,y,width,height
tint color_drawn
*/
void draw_rectangle(int x, int y, int width, int height, tint color_drawn);
/* 
Muzzle draw_rectangle_rec()
======================
Draw a rectangle to the screen
retangle rec
tint color_drawn
*/
void draw_rectangle_rec(rectangle rec, tint color_drawn);
/* 
Muzzle draw_rectangle_vec2()
======================
Draw a rectangle to the screen
vec2 pos, size
tint color_drawn
*/
void draw_rectangle_vec2(vec2 pos, vec2 size, tint color_drawn);