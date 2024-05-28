#include "core/quad_renderer.h"
#include "core/logging.h"

#define VAO 0
#define VBO 1
#define EBO 2

mz_quad_renderer mz_quad_renderer_initialize(uint32_t max_quads)
{
	mz_quad_renderer quad_renderer = (mz_quad_renderer){0};

	quad_renderer.vertices = MZ_CALLOC(max_quads * 4, sizeof(mz_quad_vertex));
	quad_renderer.max_quads = max_quads;
	quad_renderer.quad_count = 0;
	quad_renderer.vertex_index = 0;

	if (quad_renderer.vertices == NULL)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Failed to allocate memory [quad_renderer::mz_quad_renderer_initialize]");
	}

	glGenBuffers(2, &quad_renderer.buffers[VBO]);

	glGenVertexArrays(1, &quad_renderer.buffers[VAO]);
	glBindVertexArray(quad_renderer.buffers[VAO]);
	glBindBuffer(GL_ARRAY_BUFFER, quad_renderer.buffers[VBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mz_quad_vertex) * (max_quads * 4), NULL, GL_DYNAMIC_DRAW);

	quad_renderer.indices = MZ_CALLOC(max_quads * 6, sizeof(uint32_t)); // TODO: Do we need to keep these indices?
	// TODO: ^ consider GLuint because we dont know what unsigned int/GL_UNSIGNED_INT will be

	for (int i = 0, offset = 0; i < max_quads; i += 6, offset += 4)
	{
		// Triangle 1
		quad_renderer.indices[i + 0] = offset + 0;
		quad_renderer.indices[i + 1] = offset + 3;
		quad_renderer.indices[i + 2] = offset + 2;

		// Triangle 2
		quad_renderer.indices[i + 3] = offset + 0;
		quad_renderer.indices[i + 4] = offset + 1;
		quad_renderer.indices[i + 5] = offset + 3;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_renderer.buffers[EBO]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * max_quads, quad_renderer.indices, GL_STATIC_DRAW);

	glEnableVertexArrayAttrib(quad_renderer.buffers[VAO], 0);
	glVertexAttribPointer(
		/* index */ 	 0,
		/* size */ 		 2, // TODO: sizeof(vec2)?
		/* type */		 GL_FLOAT,
		/* normalized */ GL_TRUE,
		/* stride */	 sizeof(mz_quad_vertex),
		/* offset */	 (GLvoid*)(offsetof(mz_quad_vertex, position))
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

	return quad_renderer;
}

void mz_quad_renderer_flush(mz_quad_renderer* quad_renderer, float width, float height)
{
	glUseProgram(quad_renderer->shader_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_renderer->buffers[EBO]);
	glBindBuffer(GL_ARRAY_BUFFER, quad_renderer->buffers[VBO]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(mz_quad_vertex) * (quad_renderer->quad_count * 4), quad_renderer->vertices);

	// TODO: store this in struct so we dont have to keep getting if not needed
	GLint loc = glGetUniformLocation(quad_renderer->shader_id, "uViewportResolution");
	glUniform2f(loc, width, height);
	
	glBindVertexArray(quad_renderer->buffers[VAO]);
	glDrawElements(GL_TRIANGLES, quad_renderer->quad_count * 6, GL_UNSIGNED_INT, NULL);

	quad_renderer->quad_count = 0;
	quad_renderer->vertex_index = 0;
}

mz_boolean mz_quad_renderer_push_quad(mz_quad_renderer* quad_renderer, mz_quad_vertex v1, mz_quad_vertex v2, mz_quad_vertex v3, mz_quad_vertex v4)
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

void mz_quad_renderer_destroy(mz_quad_renderer* quad_renderer)
{
	glDeleteVertexArrays(1, &quad_renderer->buffers[VAO]);
	glDeleteBuffers(2, &quad_renderer->buffers[VBO]);

	MZ_FREE(quad_renderer->indices);
	MZ_FREE(quad_renderer->vertices);
}
