#pragma once
#include "../backend.h"
#include <math.h>
#include "../MuzzleMath.h"
#include "../core/vector.h"
#include "../core/tint.h"

struct _mz_circle
{
    int x,y;
    float radius;
};

/* 
Muzzle Circle
=============
int x,y;
float radius;
*/
typedef struct _mz_circle circle;


#ifdef __cplusplus
extern "C" {
#endif


/* 
Muzzle draw_circle()
======================
Draw a circle to the screen
int x,y
float radius
tint color_drawn
*/
MZ_API void draw_circle(int x, int y, float radius, tint color_drawn);

/* 
Muzzle draw_circle_type()
======================
Draw a circle to the screen
circle data
tint color_drawn
*/
MZ_API void draw_circle_type(circle data, tint color_drawn);

/* 
Muzzle draw_circle()
======================
Draw a circle to the screen
vec2 pos
float radius,
tint color_drawn
*/
MZ_API void draw_circle_vec2(vec2 pos, float radius, tint color_drawn);

#ifdef __cplusplus
}
#endif
