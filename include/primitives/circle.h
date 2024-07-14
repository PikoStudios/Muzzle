#ifndef MUZZLE_PRIMITIVES_CIRCLE_H
#define MUZZLE_PRIMITIVES_CIRCLE_H

#include "../backend.h"
#include "core/applet.h"
#include "core/tint.h"
typedef struct mz_circle
{
    float x;
    float y;
    float radius;
} mz_circle;

MZ_API void mz_draw_circle(mz_applet* applet, float x, float y, float radius, mz_tint tint);
MZ_API void mz_draw_circle_vec2(mz_applet* applet, mz_vec2 center, float radius, mz_tint tint);
MZ_API void mz_draw_circle_vec3(mz_applet* applet, mz_vec3 center_and_radius, mz_tint tint);
MZ_API void mz_draw_circle_type(mz_applet* applet, mz_circle circle, mz_tint tint);

#endif // MUZZLE_PRIMITIVES_CIRCLE_H
