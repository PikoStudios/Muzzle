#ifndef MUZZLE_CORE_BATCH_H
#define MUZZLE_CORE_BATCH_H

#include "../backend.h"
#include "Shader.h"

struct _mz_quad_vertex
{
	vec2 position;
	vec4 tint;
	vec2 texture_coordinate;
	float texture_id;
	float tiling_factor;
};

struct _mz_batch
{
	struct _mz_quad_vertex* quad_vertices;
	struct _mz_quad_vertex* quad_vertex_ptr;
	uint32_t quad_count;
	uint32_t* quad_buffers;
	shader_program quad_shader_program;
	shader_program quad_fallback_shader_program;
	uint32_t* textures;
	uint32_t texture_index;
};

typedef struct _mz_batch batch;

MZ_API batch load_batch(shader_program quad_shader);
MZ_API void unload_batch(batch* batch);

MZ_API void begin_batch(batch* batch);
MZ_API void end_batch(batch* batch);

#endif // MUZZLE_CORE_BATCH_H