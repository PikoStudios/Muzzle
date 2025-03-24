#ifndef MUZZLE_CORE_TEXT_RENDERER_H
#define MUZZLE_CORE_TEXT_RENDERER_H

#include "../backend.h"
#include "core/vector.h"
#include "core/font.h"

struct mz_text_vertex
{
	mz_vec2 position;
	mz_vec2 texture_coords;
	int texture_idx;
};

struct mz_text_renderer
{
	GLuint buffers[3];
	struct mz_text_vertex* vertices;
	uint32_t vertex_index;
	uint32_t char_count;
	uint32_t max_chars;
	GLuint shader_id;
	GLuint default_shader_id;

	mz_boolean locs_valid;
	GLint loc_uViewportResolution;
	GLint loc_uRenderOrder;
	GLint loc_uTint;
};

MZ_API struct mz_text_renderer mz_text_renderer_initialize(uint32_t max_chars);
MZ_API void mz_text_renderer_flush(struct mz_text_renderer* renderer, mz_font* font, float width, float height, int render_order, mz_vec4 tint);
MZ_API mz_boolean mz_text_renderer_push_char(struct mz_text_renderer* renderer, struct mz_text_vertex v1, struct mz_text_vertex v2, struct mz_text_vertex v3, struct mz_text_vertex v4);
MZ_API void mz_text_renderer_destroy(struct mz_text_renderer* renderer);

#endif // MUZZLE_CORE_TEXT_RENDERER_H
