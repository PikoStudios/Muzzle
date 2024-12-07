#include "core/sprite_renderer.h"
#include "core/logging.h"
#include "core/memory.h"
#include "internals/quad_indices.h"

#define LOC_UNINITIALIZED_VALUE -404

#define VAO 0
#define VBO 1
#define EBO 2

struct mz_sprite_renderer mz_sprite_renderer_initialize(uint32_t max_sprites)
{
	MZ_TRACK_FUNCTION();

	struct mz_sprite_renderer sprite_renderer = (struct mz_sprite_renderer){0};
	
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &sprite_renderer.max_textures); 
	sprite_renderer.max_textures = (sprite_renderer.max_textures <= 32) ? sprite_renderer.max_textures : 32;

	sprite_renderer.vertices = MZ_CALLOC(max_sprites * 4, sizeof(struct mz_sprite_vertex));
	sprite_renderer.vertex_index = 0;
	sprite_renderer.texture_count = 0;
	sprite_renderer.sprite_count = 0;
	sprite_renderer.max_sprites = max_sprites;

	if (sprite_renderer.vertices == NULL)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Failed to allocate memory [quad_renderer::mz_sprite_renderer_initialize::vertices]");
	}

	glGenVertexArrays(1, &sprite_renderer.buffers[VAO]);
	glGenBuffers(2, &sprite_renderer.buffers[VBO]);

	glBindVertexArray(sprite_renderer.buffers[VAO]);
	glBindBuffer(GL_ARRAY_BUFFER, sprite_renderer.buffers[VBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct mz_sprite_vertex) * (max_sprites * 4), NULL, GL_DYNAMIC_DRAW);

	GLuint* indices = MZ_CALLOC(max_sprites * 6, sizeof(GLuint));

	if (indices == NULL)
	{
		MZ_FREE(sprite_renderer.vertices);
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Failed to allocate memory [quad_renderer::mz_sprite_renderer_initialize::indices]");
	}

	internals_generate_quad_indices(indices, max_sprites);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite_renderer.buffers[EBO]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_sprites * 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);

	MZ_FREE(indices);

	glEnableVertexArrayAttrib(sprite_renderer.buffers[VAO], 0);
	glVertexAttribPointer(
		/* index */ 	 0,
		/* size */ 		 2, // TODO: sizeof(vec2)?
		/* type */		 GL_FLOAT,
		/* normalized */ GL_TRUE,
		/* stride */	 sizeof(struct mz_sprite_vertex),
		/* offset */	 (GLvoid*)(offsetof(struct mz_sprite_vertex, position))
	);
	
	glEnableVertexArrayAttrib(sprite_renderer.buffers[VAO], 1);
	glVertexAttribPointer(
		1,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(struct mz_sprite_vertex),
		(GLvoid*)(offsetof(struct mz_sprite_vertex, tint))
	);

	glEnableVertexArrayAttrib(sprite_renderer.buffers[VAO], 2);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(struct mz_sprite_vertex),
		(GLvoid*)(offsetof(struct mz_sprite_vertex, tex_coord))
	);

	glEnableVertexArrayAttrib(sprite_renderer.buffers[VAO], 3);
	glVertexAttribIPointer(
		3,
		1,
		GL_INT,
		sizeof(struct mz_sprite_vertex),
		(GLvoid*)(offsetof(struct mz_sprite_vertex, tex_id))
	);

	glEnableVertexArrayAttrib(sprite_renderer.buffers[VAO], 4);
	glVertexAttribPointer(
		4,
		1,
		GL_FLOAT,
		GL_FALSE,
		sizeof(struct mz_sprite_vertex),
		(GLvoid*)(offsetof(struct mz_sprite_vertex, tiling_factor))
	);
	
	glEnableVertexArrayAttrib(sprite_renderer.buffers[VAO], 5);
	glVertexAttribIPointer(
		5,
		1,
		GL_INT,
		sizeof(struct mz_sprite_vertex),
		(GLvoid*)(offsetof(struct mz_sprite_vertex, render_order))
	);

	sprite_renderer.locs_valid = MUZZLE_FALSE;
	sprite_renderer.loc_uViewportResolution = LOC_UNINITIALIZED_VALUE;
	sprite_renderer.loc_uTextures = LOC_UNINITIALIZED_VALUE;

	return sprite_renderer;
}

#define LOC_VERIFY(x) if (sprite_renderer->loc_##x == -1) {mz_log_status(LOG_STATUS_ERROR, "Cannot find location for \"" #x "\""); sprite_renderer->locs_valid = MUZZLE_FALSE;}

void mz_sprite_renderer_flush(struct mz_sprite_renderer* sprite_renderer, float width, float height)
{
	MZ_TRACK_FUNCTION();

	glUseProgram(sprite_renderer->shader_id);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite_renderer->buffers[EBO]);
	glBindBuffer(GL_ARRAY_BUFFER, sprite_renderer->buffers[VBO]);
	glBindVertexArray(sprite_renderer->buffers[VAO]);
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(struct mz_sprite_vertex) * (sprite_renderer->sprite_count * 4), sprite_renderer->vertices);

	if (sprite_renderer->locs_valid == MUZZLE_FALSE)
	{
		sprite_renderer->loc_uViewportResolution = glGetUniformLocation(sprite_renderer->shader_id, "uViewportResolution");
		sprite_renderer->loc_uTextures = glGetUniformLocation(sprite_renderer->shader_id, "uTextures");
		sprite_renderer->locs_valid = MUZZLE_TRUE;

		// TODO: Fix that it cannot find uniform when uniform isnt used
		LOC_VERIFY(uViewportResolution);
		LOC_VERIFY(uTextures);
	}

	// TODO: Convert texture to texture array for a lot more textures GL_TEXTURE_2D_ARRAY

	for (int i = 0; i < sprite_renderer->texture_count; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, sprite_renderer->textures[i]);
	}

	glUniform2f(sprite_renderer->loc_uViewportResolution, width, height);
	glUniform1uiv(sprite_renderer->loc_uTextures, sprite_renderer->max_textures, sprite_renderer->textures);

	glDrawElements(GL_TRIANGLES, sprite_renderer->sprite_count * 6, GL_UNSIGNED_INT, NULL);

	sprite_renderer->sprite_count = 0;
	sprite_renderer->vertex_index = 0;
	sprite_renderer->texture_count = 0;
}

int mz_sprite_renderer_push_texture(struct mz_sprite_renderer* sprite_renderer, GLint texture_id)
{
	MZ_TRACK_FUNCTION();

	MZ_ASSERT_DETAILED(texture_id > -1, "Texture ID should be guaranteed to be valid");
	
	if (sprite_renderer->texture_count + 1 > sprite_renderer->max_textures)
	{
		// Texture buffer full
		return -1;
	}
	
	for (int i = 0; i < sprite_renderer->texture_count; i++)
	{
		if (sprite_renderer->textures[i] == texture_id)
		{
			// Texture already pushed
			return i;
		}
	}

	sprite_renderer->textures[sprite_renderer->texture_count] = texture_id;
	sprite_renderer->texture_count++;

	return sprite_renderer->texture_count - 1;
}

mz_boolean mz_sprite_renderer_push_sprite(struct mz_sprite_renderer* sprite_renderer, struct mz_sprite_vertex v1, struct mz_sprite_vertex v2, struct mz_sprite_vertex v3, struct mz_sprite_vertex v4)
{
	MZ_TRACK_FUNCTION();

	MZ_ASSERT_DETAILED(v1.tex_id == v2.tex_id && v2.tex_id == v3.tex_id && v3.tex_id == v4.tex_id, "All texture ids should equal for all vertices");
	
	if (++sprite_renderer->sprite_count > sprite_renderer->max_sprites)
	{
		sprite_renderer->sprite_count--;
		return MUZZLE_FALSE;
	}

	sprite_renderer->vertices[sprite_renderer->vertex_index + 0] = v1;
	sprite_renderer->vertices[sprite_renderer->vertex_index + 1] = v2;
	sprite_renderer->vertices[sprite_renderer->vertex_index + 2] = v3;
	sprite_renderer->vertices[sprite_renderer->vertex_index + 3] = v4;

	sprite_renderer->vertex_index += 4;
	return MUZZLE_TRUE;
}

void mz_sprite_renderer_destroy(struct mz_sprite_renderer* sprite_renderer)
{
	MZ_TRACK_FUNCTION();

	glDeleteVertexArrays(1, &sprite_renderer->buffers[VAO]);
	glDeleteBuffers(2, &sprite_renderer->buffers[VBO]);
	MZ_FREE(sprite_renderer->vertices);
}
