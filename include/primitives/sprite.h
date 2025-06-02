#ifndef MUZZLE_PRIMITIVE_SPRITE_H
#define MUZZLE_PRIMITIVE_SPRITE_H

#include "../backend.h"
#include "core/applet.h"
#include "core/tint.h"
#include "core/vector.h"

typedef struct mz_sprite
{
	uint32_t width;
	uint32_t height;
	GLuint _id;
} mz_sprite;

// Sprite Batches are Muzzle's interface for sampler2DArray, only use this if you are using a custom shader that requires sampler2DArray
typedef struct mz_sprite_batch
{
	uint32_t width;
	uint32_t height;
	uint32_t size;
	GLuint id;
} mz_sprite_batch;

MZ_API mz_sprite mz_load_sprite(const char* filepath);
MZ_API void mz_unload_sprite(mz_sprite* data);

MZ_API mz_sprite_batch mz_load_sprite_batch(const char** filepaths, size_t size);
MZ_API void mz_unload_sprite_batch(mz_sprite_batch* batch);
MZ_API void mz_bind_sprite_batch(mz_applet* applet, mz_sprite_batch* batch, uint8_t texture_unit);

MZ_API void mz_bind_sprite(mz_applet* applet, mz_sprite* data, uint8_t texture_unit);

MZ_API size_t mz_read_sprite_pixels(mz_sprite* data, unsigned char* out, size_t out_len);

// TODO: Add scale and rotation as parameters
MZ_API void mz_draw_sprite(mz_applet* applet, mz_sprite* data, float x, float y, mz_tint tint);
MZ_API void mz_draw_sprite_vec2(mz_applet* applet, mz_sprite* data, mz_vec2 pos, mz_tint tint);

MZ_API void mz_draw_sprite_scaled(mz_applet* applet, mz_sprite* data, float x, float y, float scale, mz_tint tint);
MZ_API void mz_draw_sprite_scaled_vec2(mz_applet* applet, mz_sprite* data, mz_vec2 pos, float scale, mz_tint tint);

MZ_API void mz_draw_sprite_resized(mz_applet* applet, mz_sprite* data, float x, float y, uint32_t width, uint32_t height, mz_tint tint);
MZ_API void mz_draw_sprite_resized_vec2(mz_applet* applet, mz_sprite* data, mz_vec2 pos, uint32_t width, uint32_t height, mz_tint tint);

#endif // MUZZLE_PRIMITIVE_SPRITE_H
