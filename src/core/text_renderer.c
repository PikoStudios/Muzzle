#include "core/text_renderer.h"
#include "core/logging.h"

#define LOC_UNINITIALIZED_VALUE -404

struct mz_text_renderer mz_text_renderer_initialize(uint32_t max_chars)
{
	struct mz_text_renderer renderer = (struct mz_text_renderer){0};

	renderer.vertices = MZ_CALLOC(max_chars * 4, sizeof(mz_vec2));
	renderer.vertex_index = 0;
	renderer.max_chars = max_chars;
	renderer.char_count = 0;

	if (renderer.vertices == NULL)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Failed to allocate memory [text_renderer::initialize::vertices]");
	}

	glGenVertexArrays(1, &renderer.vao);
	glGenBuffers(1, &renderer.vbo);

	glBindVertexArray(renderer.vao);
	glNamedBufferData(renderer.vbo, sizeof(mz_vec2) * (max_chars * 4), NULL, GL_DYNAMIC_DRAW);

	// TODO: Make texture array

	// TODO notes
	/*
		We need to make a mz_text_vertex type
		It will need a vec2 pos and int texture_idx (index to the letter texture)

		Move texture array (sampler2DArray in shader) to mz_font. each font should hold a texture array that the
		renderer will use.
	*/

	glEnableVertexArrayAttrib(renderer.vao, 0);
	glVertexAttribDivisor(0, 1); // Tell GPU this is a per-instance attribute. Needed because we will be instancing
	glVertexAttribPointer(
		/* index */ 	 0,
		/* size */ 		 2,
		/* type */		 GL_FLOAT,
		/* normalized */ GL_TRUE,
		/* stride */	 sizeof(mz_vec2),
		/* offset */	 (GLvoid*)(0)
	);

	renderer.locs_valid = MUZZLE_FALSE;
	renderer.loc_uViewportResolution = LOC_UNINITIALIZED_VALUE;
	renderer.loc_uRenderOrderMax = LOC_UNINITIALIZED_VALUE;
	renderer.loc_uTint = LOC_UNINITIALIZED_VALUE;

	return renderer;
}

void mz_text_renderer_flush(struct mz_text_renderer* renderer, float width, float height, int render_order, mz_tint tint)
{
	
}

mz_boolean mz_text_renderer_push_char(struct mz_text_renderer* renderer, mz_vec2 v1, mz_vec2 v2, mz_vec2 v3, mz_vec2 v4)
{
	if (++renderer->char_count > renderer->max_chars)
	{
		renderer->char_count--;
		return MUZZLE_FALSE;
	}

	renderer->vertices[renderer->vertex_index + 0] = v1;
	renderer->vertices[renderer->vertex_index + 1] = v2;
	renderer->vertices[renderer->vertex_index + 2] = v3;
	renderer->vertices[renderer->vertex_index + 3] = v4;

	renderer->vertex_index += 4;
	return MUZZLE_TRUE;
}

void mz_text_renderer_destroy(struct mz_text_renderer* renderer)
{
	
}
