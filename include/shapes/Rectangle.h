#pragma once
#include "../backend.h"
#include "../core/tint.h"
#include "../core/vector.h"
#include "../core/Applet.h"

/* 
Muzzle Rectangle
================
float X
float Y
float width
float height
int index
*/
typedef struct rectangle
{
    float x;
    float y;
    float width;
    float height;
    unsigned int index;
    unsigned int parent;
} rectangle;

/*
Muzzle skinny_rectangle
================
float x
float y
float width
float height

This struct provides a rectangle-like structure without batcher index info
*/
typedef struct skinny_rectangle
{
    float x;
    float y;
    float width;
    float height;
} skinny_rectangle;

#ifdef __cplusplus
extern "C" {
#endif


/* 
Muzzle draw_rectangle()
======================
Draw a rectangle to the screen
int x,y,width,height
tint color_drawn
*/
MZ_API void draw_rectangle(int x, int y, int width, int height, tint color_drawn);
/* 
Muzzle draw_rectangle_rec()
======================
Draw a rectangle to the screen
retangle rec
tint color_drawn
*/
MZ_API void draw_rectangle_rec(Applet* applet, rectangle* rec, tint color_drawn);
/* 
Muzzle draw_rectangle_vec2()
======================
Draw a rectangle to the screen
vec2 pos, size
tint color_drawn
*/
MZ_API void draw_rectangle_vec2(vec2 pos, vec2 size, tint color_drawn);

#ifdef __cplusplus
}
#endif
