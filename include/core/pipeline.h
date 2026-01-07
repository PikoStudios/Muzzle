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

enum
{
	DEPTH_BUFFER_TYPE_RENDERBUFFER = 0,
	DEPTH_BUFFER_TYPE_TEXTURE
};

// We want this to be the same size of a boolean as it is basically a boolean
typedef mz_boolean mz_depth_buffer_type;

// NOTE: Implicitly dynamic draw buffers
typedef struct mz_vertex_buffer
{
	size_t size;
	uint32_t stride;
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
	mz_depth_buffer_type depth_buffer_type;
} mz_graphics_pipeline;

typedef struct mz_graphics_pipeline_descriptor
{
	mz_sprite_format* color_attachment_formats;
	size_t color_attachment_count;
	uint32_t framebuffer_width;
	uint32_t framebuffer_height;
	// NOTE: For **now**, all graphics pipelines will create a framebuffer
	//mz_boolean create_framebuffer; // Implicitly forced to true if color_attachments != NULL or if depth_buffer_as_texture is true

	mz_boolean create_depth_buffer; // TODO: Add a way to pass in a depth buffer texture from a different pipeline
	mz_depth_buffer_type depth_buffer_type;
} mz_graphics_pipeline_descriptor;

MZ_API mz_vertex_buffer mz_create_vertex_buffer(mz_vertex_primitive_topology_type topology_type, const mz_vertex_attribute_descriptor* attributes);
MZ_API void mz_allocate_vertex_buffer(mz_vertex_buffer* buffer, const void* data, size_t size_in_bytes);
MZ_API void mz_write_vertex_buffer(mz_vertex_buffer* buffer, const void* data, intptr_t offset, size_t size);
MZ_API void mz_unload_vertex_buffer(mz_vertex_buffer* buffer);

MZ_API mz_graphics_pipeline mz_create_graphics_pipeline(const mz_graphics_pipeline_descriptor* descriptor);
MZ_API void mz_dispatch_graphics_pipeline(mz_graphics_pipeline* pipeline, mz_vertex_buffer* buffer, );
MZ_API void mz_unload_graphics_pipeline(mz_graphics_pipeline* pipeline);

#endif // MUZZLE_CORE_PIPELINE_H
