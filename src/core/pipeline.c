#include "core/pipeline.h"
#include "backend.h"
#include "core/logging.h"

#define TYPE_SIZE_BYTE				sizeof(GLbyte)
#define TYPE_SIZE_UNSIGNED_BYTE		sizeof(GLubyte)
#define TYPE_SIZE_SHORT				sizeof(GLshort)
#define TYPE_SIZE_UNSIGNED_SHORT	sizeof(GLushort)
#define TYPE_SIZE_INT				sizeof(GLint)
#define TYPE_SIZE_UNSIGNED_INT		sizeof(GLuint)
#define TYPE_SIZE_HALF_FLOAT		sizeof(GLhalf)
#define TYPE_SIZE_FLOAT				sizeof(GLfloat)
#define TYPE_SIZE_DOUBLE			sizeof(GLdouble)

mz_vertex_buffer mz_create_vertex_buffer(mz_vertex_primitive_topology_type topology_type, const mz_vertex_attribute_descriptor* attributes, const void* data, size_t size_in_bytes)
{
	MZ_TRACK_FUNCTION();
	
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	// NOTE: Cast to GLsizeiptr is unsafe, but should be fine
	glNamedBufferData(vbo, (GLsizeiptr)(size_in_bytes), data, GL_DYNAMIC_DRAW);

	const mz_vertex_attribute_descriptor* attr = attributes;

	GLsizei stride = 0;

	// First pass: compute stride
	while (attr != NULL)
	{

// It is ugly being defined here, but it makes it clear what each case is doing
#define VERTEX_ATTRIBUTE_TYPE_STRIDE_CASE(T) case VERTEX_ATTRIBUTE_TYPE_##T: stride += TYPE_SIZE_##T; break

		switch (attr->type)
		{
			VERTEX_ATTRIBUTE_TYPE_STRIDE_CASE(BYTE);
			VERTEX_ATTRIBUTE_TYPE_STRIDE_CASE(UNSIGNED_BYTE);
			VERTEX_ATTRIBUTE_TYPE_STRIDE_CASE(SHORT);
			VERTEX_ATTRIBUTE_TYPE_STRIDE_CASE(UNSIGNED_SHORT);
			VERTEX_ATTRIBUTE_TYPE_STRIDE_CASE(INT);
			VERTEX_ATTRIBUTE_TYPE_STRIDE_CASE(UNSIGNED_INT);
			VERTEX_ATTRIBUTE_TYPE_STRIDE_CASE(HALF_FLOAT);
			VERTEX_ATTRIBUTE_TYPE_STRIDE_CASE(FLOAT);
			VERTEX_ATTRIBUTE_TYPE_STRIDE_CASE(DOUBLE);
		}
		
		attr = attr->next;
	}

	glVertexArrayVertexBuffer(vao, 0, vbo, 0, stride);

	// Second pass
	attr = attributes;
	
	GLuint index = 0;
	GLuint offset = 0;
	
	while (attr != NULL)
	{
		GLuint curr_offset = offset;
		
		glEnableVertexArrayAttrib(vao, index);

#define VERTEX_ATTRIBUTE_TYPE_ATTRIB_I_CASE(T) case VERTEX_ATTRIBUTE_TYPE_##T: offset += TYPE_SIZE_##T * attr->size; goto ATTRIB_I_FORMAT
#define VERTEX_ATTRIBUTE_TYPE_ATTRIB_F_CASE(T) case VERTEX_ATTRIBUTE_TYPE_##T: offset += TYPE_SIZE_##T * attr->size; goto ATTRIB_F_FORMAT
#define VERTEX_ATTRIBUTE_TYPE_ATTRIB_L_CASE(T) case VERTEX_ATTRIBUTE_TYPE_##T: offset += TYPE_SIZE_##T * attr->size; goto ATTRIB_L_FORMAT

		switch (attr->type)
		{
			VERTEX_ATTRIBUTE_TYPE_ATTRIB_I_CASE(BYTE);
			VERTEX_ATTRIBUTE_TYPE_ATTRIB_I_CASE(UNSIGNED_BYTE);
			VERTEX_ATTRIBUTE_TYPE_ATTRIB_I_CASE(SHORT);
			VERTEX_ATTRIBUTE_TYPE_ATTRIB_I_CASE(UNSIGNED_SHORT);
			VERTEX_ATTRIBUTE_TYPE_ATTRIB_I_CASE(INT);
			VERTEX_ATTRIBUTE_TYPE_ATTRIB_I_CASE(UNSIGNED_INT);
			VERTEX_ATTRIBUTE_TYPE_ATTRIB_F_CASE(HALF_FLOAT);
			VERTEX_ATTRIBUTE_TYPE_ATTRIB_F_CASE(FLOAT);
			VERTEX_ATTRIBUTE_TYPE_ATTRIB_L_CASE(DOUBLE);
		}

ATTRIB_I_FORMAT:
		glVertexArrayAttribIFormat(
			vao,
			index,
			attr->size,
			attr->type,
			curr_offset
		);
		goto NEXT_ATTR;

ATTRIB_F_FORMAT:
		glVertexArrayAttribFormat(
			vao,
			index,
			attr->size,
			attr->type,
			MUZZLE_FALSE,
			curr_offset
		);
		goto NEXT_ATTR;

ATTRIB_L_FORMAT:
		glVertexArrayAttribLFormat(
			vao,
			index,
			attr->size,
			GL_DOUBLE,
			curr_offset
		);

NEXT_ATTR:
		glVertexArrayAttribBinding(vao, index, 0);
		curr_offset = offset;
		index++;
		
		attr = attr->next;
	}
	
	return (mz_vertex_buffer)
	{
		.topology_type = topology_type,
		.size = size_in_bytes,
		.vao = vao,
		.vbo = vbo
	};
}

void mz_unload_vertex_buffer(mz_vertex_buffer* buffer)
{
	MZ_TRACK_FUNCTION();
	
	glDeleteBuffers(1, &buffer->vbo);
	glDeleteVertexArrays(1, &buffer->vao);

	buffer->vao = 0;
	buffer->vbo = 0;
}

mz_graphics_pipeline mz_create_graphics_pipeline(const mz_graphics_pipeline_descriptor* descriptor)
{
	MZ_TRACK_FUNCTION();
	
	mz_graphics_pipeline pipeline = (mz_graphics_pipeline){0};

	if (descriptor->framebuffer_width == 0 || descriptor->framebuffer_height == 0)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Framebuffer width and height must be greater than zero");
	}
	
	glCreateFramebuffers(1, &pipeline.fbo);

	if (descriptor->create_depth_buffer == MUZZLE_TRUE)
	{
		if (descriptor->depth_buffer_as_texture == MUZZLE_TRUE)
		{
			glCreateTextures(GL_TEXTURE_2D, 1, &pipeline.depth_buffer);
			glTextureStorage2D(pipeline.depth_buffer, 1, GL_DEPTH_COMPONENT24, descriptor->framebuffer_width, descriptor->framebuffer_height);

			glTextureParameteri(pipeline.depth_buffer, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(pipeline.depth_buffer, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTextureParameteri(pipeline.depth_buffer, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTextureParameteri(pipeline.depth_buffer, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTextureSubImage2D(pipeline.depth_buffer, 0, 0, 0, descriptor->framebuffer_width, descriptor->framebuffer_height, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			
			glNamedFramebufferTexture(pipeline.fbo, GL_DEPTH_ATTACHMENT, pipeline.depth_buffer, 0);

			pipeline.depth_buffer_type = MUZZLE_TRUE;
		}

		else
		{
			glCreateRenderbuffers(1, &pipeline.depth_buffer);
			glNamedRenderbufferStorage(pipeline.depth_buffer, GL_DEPTH_COMPONENT, descriptor->framebuffer_width, descriptor->framebuffer_height);
			glNamedFramebufferRenderbuffer(pipeline.fbo, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, pipeline.depth_buffer);

			pipeline.depth_buffer_type = MUZZLE_FALSE; // Already zero, but just to be clear
		}
	}

	MZ_ASSERT_DETAILED(descriptor->color_attachment_formats != NULL, "Color attachments must be non-null");

	if (descriptor->color_attachment_count == 0)
	{
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Graphics pipeline requires at least one color attachment");
	}

	for (int i = 0; i < descriptor->color_attachment_count; i++)
	{
		if (i >= MUZZLE_PIPELINE_MAX_COLOR_ATTACHMENTS)
		{
			mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Graphics pipeline requesting more than max color attachments (%d)", MUZZLE_PIPELINE_MAX_COLOR_ATTACHMENTS);
		}

		pipeline.color_attachments[i] = GL_COLOR_ATTACHMENT0 + i;

		GLuint texture = 0;

		glCreateTextures(1, GL_TEXTURE_2D, &texture);
		glTextureStorage2D(texture, 1, descriptor->color_attachment_formats[i], descriptor->framebuffer_width, descriptor->framebuffer_height);

		glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTextureSubImage2D(texture, 0, 0, 0, descriptor->framebuffer_width, descriptor->framebuffer_height, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		glNamedFramebufferTexture(pipeline.fbo, GL_COLOR_ATTACHMENT0 + i, texture, 0);

		pipeline.color_attachment_handles[i] = texture;
	}
	
	pipeline.color_attachments_len = descriptor->color_attachment_count;

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Could not create framebuffer"); // TODO: More in-depth error
	}

	return pipeline;
}

void mz_unload_graphics_pipeline(mz_graphics_pipeline* pipeline)
{
	MZ_TRACK_FUNCTION();

	if (pipeline->depth_buffer != 0)
	{
		switch (pipeline->depth_buffer_type)
		{
			case MUZZLE_TRUE: // Texture
				glDeleteTextures(1, &pipeline->depth_buffer);
				break;

			case MUZZLE_FALSE: // Renderbuffer
				glDeleteRenderbuffers(1, &pipeline->depth_buffer);
				break;
		}

		pipeline->depth_buffer = 0;
	}

	glDeleteTextures(pipeline->color_attachments_len, pipeline->color_attachment_handles);
	memset(pipeline->color_attachments, 0, pipeline->color_attachments_len * sizeof(mz_sprite_format));

	pipeline->color_attachments_len = 0;

	glDeleteFramebuffers(1, &pipeline->fbo);

	pipeline->fbo = 0;
}
