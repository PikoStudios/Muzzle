#include "core/pipeline.h"

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
	glDeleteBuffers(1, &buffer->vbo);
	glDeleteVertexArrays(1, &buffer->vao);
}
