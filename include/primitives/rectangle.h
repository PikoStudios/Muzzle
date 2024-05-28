#ifndef MUZZLE_PRIMITIVE_RECTANGLE_H
#define MUZZLE_PRIMITIVE_RECTANGLE_H

#include "../backend.h"
#include "../core/tint.h"
#include "core/applet.h"
#include "core/vector.h"

typedef struct mz_rectangle
{
	float x;
	float y;
	float width;
	float height;
} mz_rectangle;

MZ_API void mz_draw_rectangle(mz_applet* applet, float x, float y, float width, float height, mz_tint tint);
MZ_API void mz_draw_rectangle_vec2(mz_applet* applet, mz_vec2 position, mz_vec2 size, mz_tint tint);
MZ_API void mz_draw_rectangle_type(mz_applet* applet, mz_rectangle rec, mz_tint tint);

#endif // MUZZLE_PRIMITIVE_RECTANGLE_H
