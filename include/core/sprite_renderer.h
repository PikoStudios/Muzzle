#ifndef MUZZLE_CORE_SPRITE_RENDERER_H
#define MUZZLE_CORE_SPRITE_RENDERER_H

#include "../backend.h"
#include "vector.h"

struct mz_sprite_vertex
{
	mz_vec2 position;
	mz_vec4 tint;
	mz_vec2 tex_coord;
	float tex_id;
	float tiling_factor;
};

struct mz_sprite_renderer
{
	uint32_t buffers[3];
	struct mz_sprite_vertex* vertices;
	uint32_t vertex_index;
	uint32_t sprite_count;
//	uint32_t* textures;
	uint32_t texture_count;
	uint32_t max_textures;
	GLuint shader_id;
};

// If you are seeing this function in your autocomplete, ignore it. Unless you know you need it you dont. its mainly internal
MZ_API struct mz_sprite_renderer mz_sprite_renderer_initialize(void); // NOTE: glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits); also use DSA if available
MZ_API void mz_sprite_renderer_flush(struct mz_sprite_renderer* sprite_renderer, float width, float height);
MZ_API mz_boolean mz_sprite_renderer_push_sprite(struct mz_sprite_renderer* sprite_renderer, struct mz_sprite_vertex v1, struct mz_sprite_vertex v2, struct mz_sprite_vertex v3, struct mz_sprite_vertex v4);
MZ_API void mz_sprite_renderer_destroy(struct mz_sprite_renderer* sprite_renderer);

#endif // MUZZLE_CORE_SPRITE_RENDERER_H
