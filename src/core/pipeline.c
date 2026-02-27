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

mz_vertex_buffer mz_create_vertex_buffer(mz_vertex_primitive_topology_type topology_type, const mz_vertex_attribute_descriptor* attributes, size_t attributes_count)
{
	MZ_TRACK_FUNCTION();
	
	GLuint vao;

	glCreateVertexArrays(1, &vao);
	
	GLuint offset = 0;
	
	for (int i = 0; i < attributes_count; i++)
	{
		// Small 8-byte struct, better to copy it into 
		const mz_vertex_attribute_descriptor attr = attributes[i];
		GLuint curr_offset = offset;
		
		glEnableVertexArrayAttrib(vao, i);

#define VERTEX_ATTRIBUTE_TYPE_ATTRIB_I_CASE(T) case VERTEX_ATTRIBUTE_TYPE_##T: offset += TYPE_SIZE_##T * attr.size; goto ATTRIB_I_FORMAT
#define VERTEX_ATTRIBUTE_TYPE_ATTRIB_F_CASE(T) case VERTEX_ATTRIBUTE_TYPE_##T: offset += TYPE_SIZE_##T * attr.size; goto ATTRIB_F_FORMAT
#define VERTEX_ATTRIBUTE_TYPE_ATTRIB_L_CASE(T) case VERTEX_ATTRIBUTE_TYPE_##T: offset += TYPE_SIZE_##T * attr.size; goto ATTRIB_L_FORMAT

		switch (attr.type)
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
			i,
			attr.size,
			attr.type,
			curr_offset
		);
		goto NEXT_ATTR;

ATTRIB_F_FORMAT:
		glVertexArrayAttribFormat(
			vao,
			i,
			attr.size,
			attr.type,
			MUZZLE_FALSE,
			curr_offset
		);
		goto NEXT_ATTR;

ATTRIB_L_FORMAT:
		glVertexArrayAttribLFormat(
			vao,
			i,
			attr.size,
			GL_DOUBLE,
			curr_offset
		);

NEXT_ATTR:
		glVertexArrayAttribBinding(vao, i, 0);
		curr_offset = offset;
	}
	
	return (mz_vertex_buffer)
	{
		.topology_type = topology_type,
		.vao = vao,
		.stride = offset,
		.vbo = 0,
		.size = 0
	};
}

void mz_allocate_vertex_buffer(mz_vertex_buffer* buffer, const void* data, size_t size_in_bytes)
{
	MZ_TRACK_FUNCTION();

	glCreateBuffers(1, &buffer->vbo);

	// NOTE: Cast to GLsizeiptr is unsafe, but should be fine
	glNamedBufferData(buffer->vbo, (GLsizeiptr)(size_in_bytes), data, GL_DYNAMIC_DRAW);

	glVertexArrayVertexBuffer(buffer->vao, 0, buffer->vbo, 0, buffer->stride);

	buffer->size = size_in_bytes;
}

void mz_write_vertex_buffer(mz_vertex_buffer* buffer, const void* data, intptr_t offset, size_t size)
{
	MZ_TRACK_FUNCTION();

	MZ_ASSERT_DETAILED(size <= buffer->size, "Size cannot be larger than buffer size");
	MZ_ASSERT_DETAILED(offset <= buffer->size, "Offset cannot be past buffer end");
	MZ_ASSERT_DETAILED(offset + size <= buffer->size, "Offset+size cannot be past buffer end");

	glNamedBufferSubData(buffer->vbo, offset, size, data);
}

void mz_unload_vertex_buffer(mz_vertex_buffer* buffer)
{
	MZ_TRACK_FUNCTION();
	
	glDeleteBuffers(1, &buffer->vbo);
	glDeleteVertexArrays(1, &buffer->vao);

	buffer->vao = 0;
	buffer->vbo = 0;
	buffer->size = 0;
	buffer->stride = 0;
}

mz_graphics_pipeline mz_create_graphics_pipeline(const mz_graphics_pipeline_descriptor* descriptor)
{
	MZ_TRACK_FUNCTION();

	MZ_ASSERT_DETAILED(descriptor->shader != NULL && descriptor->shader->pid > 0, "Graphics Pipeline must have valid shader attached");
	
	mz_graphics_pipeline pipeline = (mz_graphics_pipeline){.shader = *descriptor->shader};

	if (descriptor->framebuffer_width == 0 || descriptor->framebuffer_height == 0)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Framebuffer width and height must be greater than zero");
	}
	
	MZ_TRACK_FUNCTION_STAGE("mz_create_graphics_pipeline -> framebuffer init");
	
	glCreateFramebuffers(1, &pipeline.fbo);

	if (descriptor->create_depth_buffer == MUZZLE_TRUE)
	{
		switch (descriptor->depth_buffer_type)
		{
			case DEPTH_BUFFER_TYPE_RENDERBUFFER:
				glCreateRenderbuffers(1, &pipeline.depth_buffer);
				glNamedRenderbufferStorage(pipeline.depth_buffer, GL_DEPTH_COMPONENT, descriptor->framebuffer_width, descriptor->framebuffer_height);
				glNamedFramebufferRenderbuffer(pipeline.fbo, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, pipeline.depth_buffer);
				break;

			case DEPTH_BUFFER_TYPE_TEXTURE:
				glCreateTextures(GL_TEXTURE_2D, 1, &pipeline.depth_buffer);
				glTextureStorage2D(pipeline.depth_buffer, 1, GL_DEPTH_COMPONENT24, descriptor->framebuffer_width, descriptor->framebuffer_height);

				glTextureParameteri(pipeline.depth_buffer, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTextureParameteri(pipeline.depth_buffer, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTextureParameteri(pipeline.depth_buffer, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTextureParameteri(pipeline.depth_buffer, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				
				glNamedFramebufferTexture(pipeline.fbo, GL_DEPTH_ATTACHMENT, pipeline.depth_buffer, 0);
				break;
		}

		pipeline.depth_buffer_type = descriptor->depth_buffer_type;
	}

	MZ_ASSERT_DETAILED(descriptor->color_attachment_formats != NULL, "Color attachments must be non-null");

	if (descriptor->color_attachment_count == 0)
	{
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Graphics pipeline requires at least one color attachment");
	}

	MZ_TRACK_FUNCTION_STAGE("mz_create_graphics_pipeline -> color attachment init");
	
	GLenum color_attachments[MUZZLE_PIPELINE_MAX_COLOR_ATTACHMENTS];

	for (int i = 0; i < descriptor->color_attachment_count; i++)
	{
		if (i >= MUZZLE_PIPELINE_MAX_COLOR_ATTACHMENTS)
		{
			mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Graphics pipeline requesting more than max color attachments (%d)", MUZZLE_PIPELINE_MAX_COLOR_ATTACHMENTS);
		}

		color_attachments[i] = GL_COLOR_ATTACHMENT0 + i;

		GLuint texture = 0;

		glCreateTextures(GL_TEXTURE_2D, 1, &texture);
		glTextureStorage2D(texture, 1, descriptor->color_attachment_formats[i], descriptor->framebuffer_width, descriptor->framebuffer_height);

		glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glNamedFramebufferTexture(pipeline.fbo, GL_COLOR_ATTACHMENT0 + i, texture, 0);

		pipeline.color_attachment_handles[i] = texture;
		pipeline.color_attachment_formats[i] = descriptor->color_attachment_formats[i];
	}
	
	pipeline.color_attachments_len = descriptor->color_attachment_count;

	if (glCheckNamedFramebufferStatus(pipeline.fbo, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		mz_log_status(LOG_STATUS_FATAL_ERROR, "Could not create framebuffer"); // TODO: More in-depth error
	}
	
	MZ_TRACK_FUNCTION_STAGE("mz_create_graphics_pipeline -> framebuffer draw buffers init");

	glNamedFramebufferDrawBuffers(pipeline.fbo, pipeline.color_attachments_len, color_attachments);

	pipeline.framebuffer_width = descriptor->framebuffer_width;
	pipeline.framebuffer_height = descriptor->framebuffer_height;

	return pipeline;
}

void mz_dispatch_graphics_pipeline(mz_graphics_pipeline* pipeline, mz_vertex_buffer* buffer, uint32_t start, uint32_t count)
{
	MZ_TRACK_FUNCTION();
	
	glUseProgram(pipeline->shader.pid);
	glBindVertexArray(buffer->vao);
	glBindFramebuffer(GL_FRAMEBUFFER, pipeline->fbo);

	// TODO: Eventually add an option to have an EBO
	glDrawArrays(buffer->topology_type, start, count);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void mz_clear_graphics_pipeline_color_attachments(mz_graphics_pipeline* pipeline, mz_tint clear_color)
{
	MZ_TRACK_FUNCTION();

	float color[4] = { clear_color.r / 255.f, clear_color.g / 255.f, clear_color.b / 255.f, clear_color.a / 255.f };

	for (int i = 0; i < pipeline->color_attachments_len; i++)
	{
		glClearNamedFramebufferfv(pipeline->fbo, GL_COLOR, i, color);
	}
}

void mz_clear_graphics_pipeline_depth_buffer(mz_graphics_pipeline* pipeline, float clear_value)
{
	MZ_TRACK_FUNCTION();

	glClearNamedFramebufferfv(pipeline->fbo, GL_DEPTH, 0, &clear_value);
}

mz_sprite mz_get_graphics_pipeline_color_attachment_texture(mz_graphics_pipeline* pipeline, uint8_t index)
{
	MZ_TRACK_FUNCTION();
	
	if (index >= pipeline->color_attachments_len)
	{
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Color attachment index %d out of bounds", index);
	}
	
	return (mz_sprite)
	{
		.width = pipeline->framebuffer_width,
		.height = pipeline->framebuffer_height,
		._format = pipeline->color_attachment_formats[index],
		._id = pipeline->color_attachment_handles[index]
	};
}

mz_sprite mz_get_graphics_pipeline_depth_buffer_texture(mz_graphics_pipeline* pipeline)
{
	MZ_TRACK_FUNCTION();
	
	if (pipeline->depth_buffer_type == DEPTH_BUFFER_TYPE_RENDERBUFFER)
	{
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "Depth buffer is of type renderbuffer, not texture");
	}

	return (mz_sprite)
	{
		.width = pipeline->framebuffer_width,
		.height = pipeline->framebuffer_height,
		._format = GL_DEPTH_COMPONENT24,
		._id = pipeline->depth_buffer
	};
}

void mz_unload_graphics_pipeline(mz_graphics_pipeline* pipeline)
{
	MZ_TRACK_FUNCTION();

	if (pipeline->depth_buffer != 0)
	{
		switch (pipeline->depth_buffer_type)
		{
			case DEPTH_BUFFER_TYPE_TEXTURE: // Texture
				glDeleteTextures(1, &pipeline->depth_buffer);
				break;

			case DEPTH_BUFFER_TYPE_RENDERBUFFER: // Renderbuffer
				glDeleteRenderbuffers(1, &pipeline->depth_buffer);
				break;
		}

		pipeline->depth_buffer = 0;
	}

	glDeleteTextures(pipeline->color_attachments_len, pipeline->color_attachment_handles);
	memset(pipeline->color_attachment_handles, 0, pipeline->color_attachments_len * sizeof(GLuint));

	pipeline->color_attachments_len = 0;

	glDeleteFramebuffers(1, &pipeline->fbo);

	pipeline->fbo = 0;
}
