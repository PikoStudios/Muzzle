#ifndef MUZZLE_CORE_CIRCLE_RENDERER_H
#define MUZZLE_CORE_CIRCLE_RENDERER_H

#include "../backend.h"
#include "core/vector.h"

struct mz_circle_vertex
{
	mz_vec2 position;
	mz_vec2 center;
	mz_vec4 tint;
	float radius;
	int render_order;
};

struct mz_circle_renderer
{
	uint32_t buffers[3];
	struct mz_circle_vertex* vertices;
	uint32_t vertex_index;
	uint32_t circle_count;
	uint32_t max_circles;
	GLuint shader_id;

	mz_boolean locs_valid;
	GLint loc_uViewportResolution;
};

MZ_API struct mz_circle_renderer mz_circle_renderer_initialize(uint32_t max_circles);
MZ_API void mz_circle_renderer_flush(struct mz_circle_renderer* circle_renderer, float width, float height);
MZ_API mz_boolean mz_circle_renderer_push_circle(struct mz_circle_renderer* circle_renderer, struct mz_circle_vertex v1, struct mz_circle_vertex v2, struct mz_circle_vertex v3, struct mz_circle_vertex v4);
MZ_API void mz_circle_renderer_destroy(struct mz_circle_renderer* circle_renderer);

#endif // MUZZLE_CORE_CIRCLE_RENDERER_H
