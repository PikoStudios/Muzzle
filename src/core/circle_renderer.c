#include "core/circle_renderer.h"
#include "backend.h"
#include "core/logging.h"
#include "internals/quad_indices.h"
#include <stdio.h>

#define LOC_UNINITIALIZED_VALUE -404
#define VAO 0
#define VBO 1
#define EBO 2

struct mz_circle_renderer mz_circle_renderer_initialize(uint32_t max_circles)
{
	MZ_TRACK_FUNCTION();

	struct mz_circle_renderer renderer = (struct mz_circle_renderer){0};

	renderer.vertices = MZ_CALLOC(max_circles * 4, sizeof(struct mz_circle_vertex));
	renderer.max_circles = max_circles;
	renderer.circle_count = 0;
	renderer.vertex_index = 0;
	
	if (renderer.vertices == NULL)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Failed to allocate memory [circle_renderer::mz_circle_renderer_initialize::vertices]");
	}

	glGenBuffers(2, &renderer.buffers[VBO]);
	glGenVertexArrays(1, &renderer.buffers[VAO]);

	glBindVertexArray(renderer.buffers[VAO]);
	glBindBuffer(GL_ARRAY_BUFFER, renderer.buffers[VBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct mz_circle_vertex) * max_circles, NULL, GL_DYNAMIC_DRAW);

	GLuint* indices = MZ_CALLOC(max_circles * 6, sizeof(GLuint));

	if (indices == NULL)
	{
		MZ_FREE(renderer.vertices);
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Failed to allocte memory [circle_renderer::mz_circle_renderer_initialize::indices]");
	}

	internals_generate_quad_indices(indices, max_circles);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer.buffers[EBO]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * max_circles * sizeof(GLuint), indices, GL_STATIC_DRAW);

	MZ_FREE(indices);

	glEnableVertexArrayAttrib(renderer.buffers[VAO], 0);
	glVertexAttribPointer(
		/* index */ 	 0,
		/* size */ 		 2, // TODO: sizeof(vec2)?
		/* type */		 GL_FLOAT,
		/* normalized */ GL_TRUE,
		/* stride */	 sizeof(struct mz_circle_vertex),
		/* offset */	 (GLvoid*)(offsetof(struct mz_circle_vertex, position))
	);

	glEnableVertexArrayAttrib(renderer.buffers[VAO], 1);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(struct mz_circle_vertex),
		(GLvoid*)(offsetof(struct mz_circle_vertex, center))
	);
	
	glEnableVertexArrayAttrib(renderer.buffers[VAO], 2);
	glVertexAttribPointer(
		2,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(struct mz_circle_vertex),
		(GLvoid*)(offsetof(struct mz_circle_vertex, tint))
	);
	
	glEnableVertexArrayAttrib(renderer.buffers[VAO], 3);
	glVertexAttribPointer(
		3,
		1,
		GL_FLOAT,
		GL_FALSE,
		sizeof(struct mz_circle_vertex),
		(GLvoid*)(offsetof(struct mz_circle_vertex, radius))
	);

	glEnableVertexArrayAttrib(renderer.buffers[VAO], 4);
	glVertexAttribIPointer(
		4,
		1,
		GL_INT,
		sizeof(struct mz_circle_vertex),
		(GLvoid*)(offsetof(struct mz_circle_vertex, render_order))
	);

	renderer.locs_valid = MUZZLE_FALSE;
	renderer.loc_uViewportResolution = LOC_UNINITIALIZED_VALUE;

	return renderer;
}


#define LOC_VERIFY(x) if (circle_renderer->loc_##x == -1) {mz_log_status(LOG_STATUS_ERROR, "Cannot find location for \"" #x "\""); circle_renderer->locs_valid = MUZZLE_FALSE;}

void mz_circle_renderer_flush(struct mz_circle_renderer* circle_renderer, float width, float height)
{
	MZ_TRACK_FUNCTION();

	glUseProgram(circle_renderer->shader_id);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, circle_renderer->buffers[EBO]);
	glBindBuffer(GL_ARRAY_BUFFER, circle_renderer->buffers[VBO]);
	glBindVertexArray(circle_renderer->buffers[VAO]);
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(struct mz_circle_vertex) * (circle_renderer->circle_count * 4), circle_renderer->vertices);

	if (circle_renderer->locs_valid == MUZZLE_FALSE)
	{
		circle_renderer->loc_uViewportResolution = glGetUniformLocation(circle_renderer->shader_id, "uViewportResolution");
		circle_renderer->locs_valid = MUZZLE_TRUE;

		LOC_VERIFY(uViewportResolution);
	}

	glUniform2f(circle_renderer->loc_uViewportResolution, width, height);

	glDrawElements(GL_TRIANGLES, circle_renderer->circle_count * 6, GL_UNSIGNED_INT, NULL);

	circle_renderer->circle_count = 0;
	circle_renderer->vertex_index = 0;
}

mz_boolean mz_circle_renderer_push_circle(struct mz_circle_renderer* circle_renderer, struct mz_circle_vertex v1, struct mz_circle_vertex v2, struct mz_circle_vertex v3, struct mz_circle_vertex v4)
{
	MZ_TRACK_FUNCTION();

	if (++circle_renderer->circle_count > circle_renderer->max_circles)
	{
		circle_renderer->circle_count--;
		return MUZZLE_FALSE;
	}

	circle_renderer->vertices[circle_renderer->vertex_index + 0] = v1;
	circle_renderer->vertices[circle_renderer->vertex_index + 1] = v2;
	circle_renderer->vertices[circle_renderer->vertex_index + 2] = v3;
	circle_renderer->vertices[circle_renderer->vertex_index + 3] = v4;

	circle_renderer->vertex_index += 4;
	return MUZZLE_TRUE;
}

void mz_circle_renderer_destroy(struct mz_circle_renderer* circle_renderer)
{
	MZ_TRACK_FUNCTION();

	glDeleteProgram(circle_renderer->shader_id);
	glDeleteVertexArrays(1, &circle_renderer->buffers[VAO]);
	glDeleteBuffers(2, &circle_renderer->buffers[VBO]);

	MZ_FREE(circle_renderer->vertices);
}
