#include "core/quad_renderer.h"
#include "core/logging.h"
#include <stdio.h>

#define LOC_UNINITIALIZED_VALUE -404

#define VAO 0
#define VBO 1
#define EBO 2

struct mz_quad_renderer mz_quad_renderer_initialize(uint32_t max_quads)
{
	struct mz_quad_renderer quad_renderer = (struct mz_quad_renderer){0};

	quad_renderer.vertices = MZ_CALLOC(max_quads * 4, sizeof(struct mz_quad_vertex));
	quad_renderer.max_quads = max_quads;
	quad_renderer.quad_count = 0;
	quad_renderer.vertex_index = 0;

	if (quad_renderer.vertices == NULL)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Failed to allocate memory [quad_renderer::mz_quad_renderer_initialize::vertices]");
	}

	glGenBuffers(2, &quad_renderer.buffers[VBO]);

	glGenVertexArrays(1, &quad_renderer.buffers[VAO]);
	glBindVertexArray(quad_renderer.buffers[VAO]);
	glBindBuffer(GL_ARRAY_BUFFER, quad_renderer.buffers[VBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct mz_quad_vertex) * (max_quads * 4), NULL, GL_DYNAMIC_DRAW);

	GLuint* indices = MZ_CALLOC(max_quads * 6, sizeof(GLuint));

	if (indices == NULL)
	{
		MZ_FREE(quad_renderer.vertices);
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Failed to allocate memory [quad_renderer::mz_quad_renderer_initialize::indices]");
	}

	for (int i = 0, offset = 0; i < max_quads; i += 6, offset += 4)
	{
		// Triangle 1
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 3;
		indices[i + 2] = offset + 2;

		// Triangle 2
		indices[i + 3] = offset + 0;
		indices[i + 4] = offset + 1;
		indices[i + 5] = offset + 3;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_renderer.buffers[EBO]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * max_quads, indices, GL_STATIC_DRAW);

	MZ_FREE(indices);

	glEnableVertexArrayAttrib(quad_renderer.buffers[VAO], 0);
	glVertexAttribPointer(
		/* index */ 	 0,
		/* size */ 		 2, // TODO: sizeof(vec2)?
		/* type */		 GL_FLOAT,
		/* normalized */ GL_TRUE,
		/* stride */	 sizeof(struct mz_quad_vertex),
		/* offset */	 (GLvoid*)(offsetof(struct mz_quad_vertex, position))
	);

	glEnableVertexArrayAttrib(quad_renderer.buffers[VAO], 1);
	glVertexAttribPointer(
		1,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(struct mz_quad_vertex),
		(GLvoid*)(offsetof(struct mz_quad_vertex, tint))
	);

	glEnableVertexArrayAttrib(quad_renderer.buffers[VAO], 2);
	glVertexAttribIPointer(
		2,
		1,
		GL_INT,
		sizeof(struct mz_quad_vertex),
		(GLvoid*)(offsetof(struct mz_quad_vertex, render_order))
	);
	
	quad_renderer.locs_valid = MUZZLE_FALSE;
	quad_renderer.loc_uViewportResolution = LOC_UNINITIALIZED_VALUE;
	quad_renderer.loc_uRenderOrderMax = LOC_UNINITIALIZED_VALUE;

	return quad_renderer;
}

#define LOC_VERIFY(x) if (quad_renderer->loc_##x == -1) {mz_log_status(LOG_STATUS_ERROR, "Cannot find location for \"" #x "\""); quad_renderer->locs_valid = MUZZLE_FALSE;}

void mz_quad_renderer_flush(struct mz_quad_renderer* quad_renderer, float width, float height, int render_order)
{
	glUseProgram(quad_renderer->shader_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_renderer->buffers[EBO]);
	glBindBuffer(GL_ARRAY_BUFFER, quad_renderer->buffers[VBO]);
	glBindVertexArray(quad_renderer->buffers[VAO]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(struct mz_quad_vertex) * (quad_renderer->quad_count * 4), quad_renderer->vertices);

	// TODO: profile to see if this is actually faster than just fetching the uniform location every frame
	if (quad_renderer->locs_valid == MUZZLE_FALSE)
	{
		quad_renderer->loc_uViewportResolution = glGetUniformLocation(quad_renderer->shader_id, "uViewportResolution");
		quad_renderer->loc_uRenderOrderMax = glGetUniformLocation(quad_renderer->shader_id, "uRenderOrderMax");
		quad_renderer->locs_valid = MUZZLE_TRUE;

		// TODO: Fix that it cannot find uniform when uniform isnt used
		LOC_VERIFY(uViewportResolution);
		LOC_VERIFY(uRenderOrderMax);
	}

	// TODO: see if there is a elegant way to not update every frame
	glUniform2f(quad_renderer->loc_uViewportResolution, width, height);
	glUniform1i(quad_renderer->loc_uRenderOrderMax, render_order);
	
	glDrawElements(GL_TRIANGLES, quad_renderer->quad_count * 6, GL_UNSIGNED_INT, NULL);

	quad_renderer->quad_count = 0;
	quad_renderer->vertex_index = 0;
}

mz_boolean mz_quad_renderer_push_quad(struct mz_quad_renderer* quad_renderer, struct mz_quad_vertex v1, struct mz_quad_vertex v2, struct mz_quad_vertex v3, struct mz_quad_vertex v4)
{
	if (++quad_renderer->quad_count > quad_renderer->max_quads)
	{
		quad_renderer->quad_count--;
		return MUZZLE_FALSE;
	}

	quad_renderer->vertices[quad_renderer->vertex_index + 0] = v1;
	quad_renderer->vertices[quad_renderer->vertex_index + 1] = v2;
	quad_renderer->vertices[quad_renderer->vertex_index + 2] = v3;
	quad_renderer->vertices[quad_renderer->vertex_index + 3] = v4;

	quad_renderer->vertex_index += 4;
	return MUZZLE_TRUE;
}

void mz_quad_renderer_destroy(struct mz_quad_renderer* quad_renderer)
{
	glDeleteVertexArrays(1, &quad_renderer->buffers[VAO]);
	glDeleteBuffers(2, &quad_renderer->buffers[VBO]);

	MZ_FREE(quad_renderer->vertices);
}
