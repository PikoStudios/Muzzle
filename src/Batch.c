#include "core/Batch.h"

batch load_batch(shader_program quad_shader)
{
	batch buffer;
	buffer.quad_fallback_shader_program = quad_shader;
	buffer.quad_shader_program = buffer.quad_fallback_shader_program;
	buffer.quad_buffers = MZ_CALLOC(3, sizeof(uint32_t));
	
	if (buffer.quad_buffers == NULL)
	{
		log_status(STATUS_FATAL_ERROR, "Failed to allocate memory for quad buffers");
	}
	
	buffer.quad_vertices = MZ_CALLOC(MUZZLE_BATCH_QUAD_MAX * 4, sizeof(struct _mz_quad_vertex));
	buffer.quad_vertex_ptr = buffer.quad_vertices;
	buffer.quad_count = 0;
	
	if (buffer.quad_vertices == NULL)
	{
		log_status(STATUS_FATAL_ERROR, "Failed to allocate memory for quad vertices");
	}
	
	buffer.textures = MZ_CALLOC(32, sizeof(uint32_t));
	buffer.texture_index = 0;
	
	if (buffer.textures == NULL)
	{
		log_status(STATUS_FATAL_ERROR, "Failed to allocate memory for textures");
	}
	
	// TODO: If i switch to OpenGL 3.3, figure out an alternative to glTextureStorage2D
	// AKA glBindTexture
	
	glCreateTextures(GL_TEXTURE_2D, 1, &buffer.textures[0]);
	glTextureStorage2D(buffer.textures[0], 1, GL_RGBA8, 1, 1);
	
	glTextureParameteri(buffer.textures[0], GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(buffer.textures[0], GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(buffer.textures[0], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(buffer.textures[0], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	uint32_t white_color = 0xffffffff;
	glTextureSubImage2D(buffer.textures[0], 0, 0, 0, 1, 1, GL_RGBA8, GL_UNSIGNED_BYTE, &white_color);
	
	uint32_t* vao = &buffer.quad_buffers[0];
	uint32_t* vbo = &buffer.quad_buffers[1];
	uint32_t* ebo = &buffer.quad_buffers[2];
	
	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);
	
	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct _mz_quad_vertex) * (MUZZLE_BATCH_QUAD_MAX * 4), NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, ebo);
	
	// not using stack because by default this would be 48 kilobytes of data
	// not best practice to have 48 kilobytes of data on stack
	uint32_t* quad_indices = MZ_CALLOC(6 * MUZZLE_BATCH_QUAD_MAX, sizeof(uint32_t));
	
	for (int i = 0; i < MUZZLE_BATCH_QUAD_MAX; i += 6)
	{
		int offset = 4 * i;
		
		// Triangle 1
		quad_indices[i + 0] = offset + 3;
		quad_indices[i + 1] = offset + 2;
		quad_indices[i + 2] = offset + 0;
		
		// Triangle 2
		quad_indices[i + 3] = offset + 0;
		quad_indices[i + 4] = offset + 2;
		quad_indices[i + 5] = offset + 1;
	}
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * MUZZLE_BATCH_QUAD_MAX, quad_indices, GL_STATIC_DRAW);
	
	MZ_FREE(quad_indices);
	
	glEnableVertexArrayAttrib(*vao, 0);
	glVertexAttribPointer(
		/* index */ 		0,
		/* size */ 			2,
		/* type */ 			GL_FLOAT,
		/* normalized */ 	GL_TRUE,
		/* stride */ 		sizeof(struct _mz_quad_vertex),
		/* offset */		(GLvoid*)(offsetof(struct _mz_quad_vertex, position)));
	
	glEnableVertexArrayAttrib(*vao, 1);
	glVertexAttribPointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(struct _mz_quad_vertex),
			(GLvoid*)(offsetof(struct _mz_quad_vertex, tint)));
	
	glEnableVertexArrayAttrib(*vao, 2);
	glVertexAttribPointer(
			2,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(struct _mz_quad_vertex),
			(GLvoid*)(offsetof(struct _mz_quad_vertex, texture_coordinate)));
	
	glEnableVertexArrayAttrib(*vao, 3);
	glVertexAttribPointer(
			3,
			1,
			GL_FLOAT,
			GL_FALSE,
			sizeof(struct _mz_quad_vertex),
			(GLvoid*)(offsetof(struct _mz_quad_vertex, texture_id)));
	
	glEnableVertexArrayAttrib(*vao, 4);
	glVertexAttribPointer(
			4,
			1,
			GL_FLOAT,
			GL_FALSE,
			sizeof(struct _mz_quad_vertex),
			(GLvoid*)(offsetof(struct _mz_quad_vertex, tiling_factor)));
	
	return buffer;
}

void unload_batch(batch* batch)
{
	glDeleteVertexArrays(1, &batch->quad_buffers[0]);
	glDeleteBuffers(1, &batch->quad_buffers[1]);
	glDeleteBuffers(1, &batch->quad_buffers[2]);
	glDeleteTextures(batch->texture_index, batch->textures);
	unload_shader_program(&batch->quad_shader_program);
	
	MZ_FREE(batch->quad_vertices);
	MZ_FREE(batch->quad_buffers);
	MZ_FREE(batch->textures);
}

void begin_batch(batch* batch)
{
	batch->quad_vertex_ptr = batch->quad_vertices;
	batch->quad_count = 0;
	// TODO: Refresh Textures
}

void end_batch(batch* batch)
{
	if (batch->quad_count > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->quad_buffers[2]);
		glBindVertexArray(batch->quad_buffers[0]);
			mat4 projection = {
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1
			};
		
			//upload_uniform_mat4(batch->quad_shader_program, "u_ViewProjectionMatrix", projection);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(struct _mz_quad_vertex) * (batch->quad_count * 4), batch->quad_vertices);
		
			glUseProgram(batch->quad_shader_program);
				GLuint loc = glGetUniformLocation(batch->quad_shader_program, "u_ViewProjectionMatrix");
				glUniformMatrix4fv(loc, 1, MUZZLE_FALSE, projection);
		
				loc = glGetUniformLocation(batch->quad_shader_program, "u_Textures");
				glUniform1iv(loc, 32, (GLint*)(batch->textures));
		
				glDrawElements(GL_TRIANGLES, batch->quad_count * 6, GL_UNSIGNED_INT, 0);
			glUseProgram(0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
