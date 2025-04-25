#ifndef MUZZLE_CORE_SPRITE_RENDERER_H
#define MUZZLE_CORE_SPRITE_RENDERER_H

#include "../backend.h"
#include "vector.h"

struct mz_sprite_vertex
{
	mz_vec2 position;
	mz_vec4 tint;
	mz_vec2 tex_coord;
	GLint tex_id;
	float tiling_factor;
	GLint render_order; // TODO: just include render order in position as Z
};

struct mz_sprite_renderer
{
	uint32_t textures[MUZZLE_SPRITE_TEXTURE_BUFFER_CAPACITY];
	uint32_t buffers[3];
	struct mz_sprite_vertex* vertices;
	uint32_t vertex_index;
	uint32_t sprite_count;
	uint32_t texture_count;
	uint32_t max_sprites;
	GLint max_textures;
	GLuint shader_id;
	GLuint default_shader_id;

	mz_boolean locs_valid;
	GLint loc_uViewportResolution;
	GLint loc_uTextures;
};

// If you are seeing this function in your autocomplete, ignore it. Unless you know you need it you dont. its mainly internal
MZ_API struct mz_sprite_renderer mz_sprite_renderer_initialize(uint32_t max_sprites, GLint max_texture_units);
MZ_API void mz_sprite_renderer_flush(struct mz_sprite_renderer* sprite_renderer, float width, float height);
MZ_API int mz_sprite_renderer_push_texture(struct mz_sprite_renderer* sprite_renderer, GLint texture_id);
MZ_API mz_boolean mz_sprite_renderer_push_sprite(struct mz_sprite_renderer* sprite_renderer, struct mz_sprite_vertex v1, struct mz_sprite_vertex v2, struct mz_sprite_vertex v3, struct mz_sprite_vertex v4);
MZ_API void mz_sprite_renderer_destroy(struct mz_sprite_renderer* sprite_renderer);

#endif // MUZZLE_CORE_SPRITE_RENDERER_H
