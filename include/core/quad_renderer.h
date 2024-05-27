#ifndef MUZZLE_CORE_QUAD_RENDERER_H
#define MUZZLE_CORE_QUAD_RENDERER_H

#include "../backend.h"
#include "vector.h"
#include <stdint.h>

typedef struct mz_quad_vertex
{
	mz_vec2 position;
	mz_vec4 tint;
} mz_quad_vertex;

typedef struct mz_quad_renderer
{
	uint32_t buffers[3];
	mz_quad_vertex* vertices;
	mz_quad_vertex* vertex_ptr;
	uint32_t quad_count;
	uint32_t max_quads;
	uint32_t* indices;
	uint32_t* vao;
	uint32_t* vbo;
	uint32_t* ebo;
	GLuint shader_id;
} mz_quad_renderer;

MZ_API mz_quad_renderer mz_quad_renderer_initialize(uint32_t max_quads);
MZ_API void mz_quad_renderer_flush(mz_quad_renderer* quad_renderer);
MZ_API void mz_quad_renderer_destroy(mz_quad_renderer* quad_renderer);

#endif // MUZZLE_CORE_QUAD_RENDERER_H
