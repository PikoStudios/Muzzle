#ifndef MUZZLE_CORE_PIPELINE_H
#define MUZZLE_CORE_PIPELINE_H

#include "../backend.h"
// TODO: Big problem, core components should not depend on non-core components
// TODO: Maybe make pipelines non-core? Would fix but then we have the issue that core-components
// TODO: Cannot use this nice abstraction
// TODO: shader.h already breaks the rule, so for now i'll keep it...
#include "../primitives/sprite.h"

typedef enum
{
	VERTEX_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE = GL_TRIANGLES,
	VERTEX_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	VERTEX_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE_FAN = GL_TRIANGLE_FAN,
	VERTEX_PRIMITIVE_TOPOLOGY_TYPE_POINT = GL_POINTS,
	VERTEX_PRIMITIVE_TOPOLOGY_TYPE_LINES = GL_LINES
} mz_vertex_primitive_topology_type;

typedef enum
{
	VERTEX_ATTRIBUTE_TYPE_BYTE = GL_BYTE,
	VERTEX_ATTRIBUTE_TYPE_UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	VERTEX_ATTRIBUTE_TYPE_SHORT = GL_SHORT,
	VERTEX_ATTRIBUTE_TYPE_UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	VERTEX_ATTRIBUTE_TYPE_INT = GL_INT,
	VERTEX_ATTRIBUTE_TYPE_UNSIGNED_INT = GL_UNSIGNED_INT,
	VERTEX_ATTRIBUTE_TYPE_HALF_FLOAT = GL_HALF_FLOAT,
	VERTEX_ATTRIBUTE_TYPE_FLOAT = GL_FLOAT,
	VERTEX_ATTRIBUTE_TYPE_DOUBLE = GL_DOUBLE,
} mz_vertex_attribute_type;

// NOTE: Implicitly dyanmic draw buffers
typedef struct mz_vertex_buffer
{
	GLsizeiptr size;
	GLuint vao;
	GLuint vbo;
	mz_vertex_primitive_topology_type topology_type;
} mz_vertex_buffer;

typedef struct mz_vertex_attribute_descriptor
{
	struct mz_vertex_attribute_descriptor* next;
	uint8_t size;
	mz_vertex_attribute_type type;
} mz_vertex_attribute_descriptor;

typedef struct mz_graphics_pipeline
{
	GLenum color_attachments[MUZZLE_PIPELINE_MAX_COLOR_ATTACHMENTS];
	GLuint color_attachment_handles[MUZZLE_PIPELINE_MAX_COLOR_ATTACHMENTS];
	uint8_t color_attachments_len;
	GLuint fbo;
	GLuint depth_buffer;
	mz_boolean depth_buffer_type; // 0 for Renderbuffer 1 for Texture
} mz_graphics_pipeline;

typedef struct mz_color_attachment_descriptor
{
	struct mz_color_attachment_descriptor* next;
	uint32_t width;
	uint32_t height;
	mz_sprite_format internal_format;
} mz_color_attachment_descriptor;

typedef struct mz_graphics_pipeline_descriptor
{
	mz_vertex_buffer buffer;
	mz_color_attachment_descriptor* color_attachments;
	mz_boolean create_framebuffer; // Implicitly forced to true if color_attachments != NULL
	mz_boolean depth_buffer_as_texture;
} mz_graphics_pipeline_descriptor;

MZ_API mz_vertex_buffer mz_create_vertex_buffer(mz_vertex_primitive_topology_type topology_type, const mz_vertex_attribute_descriptor* attributes, const void* data, size_t size_in_bytes);
MZ_API void mz_unload_vertex_buffer(mz_vertex_buffer* buffer);

#endif // MUZZLE_CORE_PIPELINE_H
