#pragma once
#include "../backend.h"
#include "../core/tint.h"
#include "../core/vector.h"
#include "../core/Applet.h"
#include "../core/Batcher.h"

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
} rectangle;

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
MZ_API void draw_rectangle(Applet* applet, int x, int y, int width, int height, tint color_drawn);
/* 
Muzzle draw_rectangle_rec()
======================
Draw a rectangle to the screen
retangle rec
tint color_drawn
*/
MZ_API void draw_rectangle_rec(Applet* applet, rectangle rec, tint color_drawn);
/* 
Muzzle draw_rectangle_vec2()
======================
Draw a rectangle to the screen
vec2 pos, size
tint color_drawn
*/
MZ_API void draw_rectangle_vec2(Applet* applet, vec2 pos, vec2 size, tint color_drawn);

#ifdef __cplusplus
}
#endif
