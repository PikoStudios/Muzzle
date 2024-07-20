#include "core/text_renderer.h"
#include "core/logging.h"
#include "internals/todo.h"

#define LOC_UNINITIALIZED_VALUE -404

struct mz_text_renderer mz_text_renderer_initialize(uint32_t max_chars)
{
	struct mz_text_renderer renderer = (struct mz_text_renderer){0};

	renderer.vertices = MZ_CALLOC(max_chars * 4, sizeof(struct mz_text_vertex));
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

	glEnableVertexArrayAttrib(renderer.vao, 0);
	glVertexAttribDivisor(0, 1); // Tell GPU this is a per-instance attribute. Needed because we will be instancing
	glVertexAttribPointer(
		/* index */ 	 0,
		/* size */ 		 2,
		/* type */		 GL_FLOAT,
		/* normalized */ GL_TRUE,
		/* stride */	 sizeof(struct mz_text_vertex),
		/* offset */	 (GLvoid*)(offsetof(struct mz_text_vertex, position))
	);

	glEnableVertexArrayAttrib(renderer.vao, 1);
	glVertexAttribDivisor(1, 1);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(struct mz_text_vertex),
		(GLvoid*)(offsetof(struct mz_text_vertex, texture_coords))
	);

	glEnableVertexArrayAttrib(renderer.vao, 2);
	glVertexAttribDivisor(2, 1);
	glVertexAttribIPointer(
		2,
		1,
		GL_INT,
		sizeof(struct mz_text_vertex),
		(GLvoid*)(offsetof(struct mz_text_vertex, texture_idx))
	);

	renderer.locs_valid = MUZZLE_FALSE;
	renderer.loc_uViewportResolution = LOC_UNINITIALIZED_VALUE;
	renderer.loc_uTint = LOC_UNINITIALIZED_VALUE;
	renderer.loc_uRenderOrder = LOC_UNINITIALIZED_VALUE;

	return renderer;
}

#define LOC_VERIFY(x) if (renderer->loc_##x == -1) {mz_log_status(LOG_STATUS_ERROR, "Cannot find location for \"" #x "\""); renderer->locs_valid = MUZZLE_FALSE;}

void mz_text_renderer_flush(struct mz_text_renderer* renderer, mz_font* font, float width, float height, int render_order, mz_vec4 tint)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glUseProgram(renderer->shader_id);

	glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
	glBindVertexArray(renderer->vao);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(struct mz_text_vertex) * (renderer->char_count * 4), renderer->vertices); // Sadly glNamedBufferSubData() isn't well documented so I will stick with the binding approach
	
	if (renderer->locs_valid == MUZZLE_FALSE)
	{
		renderer->loc_uViewportResolution = glGetUniformLocation(renderer->shader_id, "uViewportResolution");
		renderer->loc_uRenderOrder = glGetUniformLocation(renderer->shader_id, "uRenderOrder");
		renderer->loc_uTint = glGetUniformLocation(renderer->shader_id, "uTint");

		LOC_VERIFY(uViewportResolution);
		LOC_VERIFY(uRenderOrder);
		LOC_VERIFY(uTint);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, font->texture_array_id);

	glUniform2f(renderer->loc_uViewportResolution, width, height);
	glUniform1i(renderer->loc_uRenderOrder, render_order);
	glUniform4f(renderer->loc_uTint, tint.x, tint.y, tint.z, tint.w);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, renderer->char_count);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	renderer->char_count = 0;
	renderer->vertex_index = 0;
}

mz_boolean mz_text_renderer_push_char(struct mz_text_renderer* renderer, struct mz_text_vertex v1, struct mz_text_vertex v2, struct mz_text_vertex v3, struct mz_text_vertex v4)
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
	glDeleteVertexArrays(1, &renderer->vao);
	glDeleteBuffers(1, &renderer->vbo);
	
	MZ_FREE(renderer->vertices);
}
