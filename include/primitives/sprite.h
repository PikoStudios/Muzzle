#ifndef MUZZLE_PRIMITIVE_SPRITE_H
#define MUZZLE_PRIMITIVE_SPRITE_H

#include "../backend.h"
#include "core/applet.h"
#include "core/tint.h"
#include "core/vector.h"

typedef struct mz_sprite
{
	int width;
	int height;
	GLuint _id;
} mz_sprite;

MZ_API mz_sprite mz_load_sprite(const char* filepath);
MZ_API void mz_unload_sprite(mz_sprite* data);

// TODO: Add scale and rotation as parameters
MZ_API void mz_draw_sprite(mz_applet* applet, mz_sprite* data, float x, float y, mz_tint tint);
MZ_API void mz_draw_sprite_vec2(mz_applet* applet, mz_sprite* data, mz_vec2 pos, mz_tint tint);

#endif // MUZZLE_PRIMITIVE_SPRITE_H
