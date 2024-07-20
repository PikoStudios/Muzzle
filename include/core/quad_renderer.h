#ifndef MUZZLE_CORE_QUAD_RENDERER_H
#define MUZZLE_CORE_QUAD_RENDERER_H

#include "../backend.h"
#include "vector.h"
#include <stdint.h>

struct mz_quad_vertex
{
	mz_vec2 position;
	mz_vec4 tint;
	GLint render_order; // TODO: Just include in position
};

struct mz_quad_renderer
{
	uint32_t buffers[3];
	struct mz_quad_vertex* vertices;
	uint32_t vertex_index;
	uint32_t quad_count;
	uint32_t max_quads;
	GLuint shader_id;

	// Locations. If a lot is needed then make it into a inner struct
	mz_boolean locs_valid;
	GLint loc_uViewportResolution;
};

MZ_API struct mz_quad_renderer mz_quad_renderer_initialize(uint32_t max_quads);
MZ_API void mz_quad_renderer_flush(struct mz_quad_renderer* quad_renderer, float width, float height);
MZ_API mz_boolean mz_quad_renderer_push_quad(struct mz_quad_renderer* quad_renderer, struct mz_quad_vertex v1, struct mz_quad_vertex v2, struct mz_quad_vertex v3, struct mz_quad_vertex v4);
MZ_API void mz_quad_renderer_destroy(struct mz_quad_renderer* quad_renderer);

#endif // MUZZLE_CORE_QUAD_RENDERER_H
