#ifndef MUZZLE_CORE_TEXT_RENDERER_H
#define MUZZLE_CORE_TEXT_RENDERER_H

#include "../backend.h"
#include "core/multidraw_indirect.h"
#include "core/tint.h"
#include "core/vector.h"

struct mz_text_renderer
{
	GLuint vao;
	GLuint vbo;
	mz_vec2* vertices;
	uint32_t vertex_index;
	GLuint texture_array;
	uint32_t char_count;
	uint32_t max_chars;
	GLuint shader_id;

	mz_boolean locs_valid;
	GLint loc_uViewportResolution;
	GLint loc_uRenderOrderMax;
	GLint loc_uTint;
};

MZ_API struct mz_text_renderer mz_text_renderer_initialize(uint32_t max_chars);
MZ_API void mz_text_renderer_flush(struct mz_text_renderer* renderer, float width, float height, int render_order, mz_tint tint);
MZ_API mz_boolean mz_text_renderer_push_char(struct mz_text_renderer* renderer, mz_vec2 v1, mz_vec2 v2, mz_vec2 v3, mz_vec2 v4);
MZ_API void mz_text_renderer_destroy(struct mz_text_renderer* renderer);

#endif // MUZZLE_CORE_TEXT_RENDERER_H
