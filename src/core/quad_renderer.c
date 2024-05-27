#include "core/quad_renderer.h"
#include "core/logging.h"

mz_quad_renderer mz_quad_renderer_initialize(uint32_t max_quads)
{
	mz_quad_renderer quad_renderer = (mz_quad_renderer){0};

	quad_renderer.vertices = MZ_CALLOC(max_quads * 4, sizeof(mz_quad_vertex));
	quad_renderer.max_quads = max_quads;
	quad_renderer.quad_count = 0;

	if (quad_renderer.vertices == NULL)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Failed to allocate memory [quad_renderer::mz_quad_renderer_initialize]");
	}

	quad_renderer.vertex_ptr = quad_renderer.vertices;

	glGenBuffers(2, quad_renderer.buffers);

	quad_renderer.vao = &quad_renderer.buffers[0];
	quad_renderer.vbo = &quad_renderer.buffers[1];
	quad_renderer.ebo = &quad_renderer.buffers[2];

	glGenVertexArrays(1, quad_renderer.vao);
	glBindVertexArray(*quad_renderer.vao);
	glBindBuffer(GL_ARRAY_BUFFER, *quad_renderer.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mz_quad_vertex) * (max_quads * 4), NULL, GL_DYNAMIC_DRAW);

	quad_renderer.indices = MZ_CALLOC(max_quads * 6, sizeof(uint32_t)); // TODO: Do we need to keep these indices?
	// TODO: ^ consider GLuint because we dont know what unsigned int/GL_UNSIGNED_INT will be

	for (int i = 0; i < max_quads; i += 6)
	{
		int offset = 4 * i;

		// Triangle 1
		quad_renderer.indices[i + 0] = offset + 3;
		quad_renderer.indices[i + 1] = offset + 2;
		quad_renderer.indices[i + 2] = offset + 0;

		// Triangle 2
		quad_renderer.indices[i + 3] = offset + 0;
		quad_renderer.indices[i + 4] = offset + 2;
		quad_renderer.indices[i + 5] = offset + 1;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *quad_renderer.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * max_quads, quad_renderer.indices, GL_STATIC_DRAW);

	glEnableVertexArrayAttrib(*quad_renderer.vao, 0);
	glVertexAttribPointer(
		/* index */ 	 0,
		/* size */ 		 2, // TODO: sizeof(vec2)?
		/* type */		 GL_FLOAT,
		/* normalized */ GL_TRUE,
		/* stride */	 sizeof(mz_quad_vertex),
		/* offset */	 (GLvoid*)(offsetof(mz_quad_vertex, position))
	);

	glEnableVertexArrayAttrib(*quad_renderer.vao, 1);
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

void mz_quad_renderer_flush(mz_quad_renderer* quad_renderer)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *quad_renderer->ebo);
	glBindVertexArray(*quad_renderer->vao);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(mz_quad_vertex) * (quad_renderer->quad_count * 4), quad_renderer->vertices);

	glUseProgram(quad_renderer->shader_id);
	glDrawElements(GL_TRIANGLES, quad_renderer->quad_count * 6, GL_UNSIGNED_INT, NULL);
}

void mz_quad_renderer_destroy(mz_quad_renderer* quad_renderer)
{
	glDeleteVertexArrays(1, quad_renderer->vao);
	glDeleteBuffers(2, &quad_renderer->buffers[1]);

	MZ_FREE(quad_renderer->indices);
	MZ_FREE(quad_renderer->vertices);
}
