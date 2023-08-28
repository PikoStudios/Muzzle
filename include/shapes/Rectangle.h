#ifndef MUZZLE_SHAPES_RECTANGLE_H
#define MUZZLE_SHAPES_RECTANGLE_H

#ifdef MUZZLE_INCLUDE_UTILS
    #define RECTANGLE(x,y,w,h) (rectangle){x,y,w,h};
#endif

#include "../backend.h"
#include "../core/tint.h"
#include "../core/vector.h"
#include "../core/Batch.h"
#include "../core/Applet.h"
#include "../core/Error.h"

struct _mz_rectangle
{
    float x;
    float y;
    float width;
    float height;
};

typedef struct _mz_rectangle rectangle;

MZ_API void draw_rectangle_rec(rectangle rec, tint color_drawn);
MZ_API void draw_rectangle_vec2(vec2 position, vec2 size, tint color_drawn);
MZ_API void draw_rectangle(float x, float y, float width, float height, tint color_drawn);

#endif // MUZZLE_SHAPES_RECTANGLE_H