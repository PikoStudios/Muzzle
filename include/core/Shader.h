#ifndef MUZZLE_CORE_SHADER_H
#define MUZZLE_CORE_SHADER_H

#include "../backend.h"
#include "Error.h"

enum _mz_shader_type
{
	SHADER_VERTEX=GL_VERTEX_SHADER,
	SHADER_FRAGMENT=GL_FRAGMENT_SHADER
};

enum _mz_vertex_attribute_type
{
	ATTRIB_TYPE_BYTE=GL_BYTE,
	ATTRIB_TYPE_UBYTE=GL_UNSIGNED_BYTE,
	ATTRIB_TYPE_SHORT=GL_SHORT,
	ATTRIB_TYPE_USHORT=GL_UNSIGNED_SHORT,
	ATTRIB_TYPE_INT=GL_INT,
	ATTRIB_TYPE_UINT=GL_UNSIGNED_INT,
	ATTRIB_TYPE_FLOAT=GL_FLOAT
};

struct _mz_vertex_attribute_buffer
{
	GLuint program;
	intptr_t* attributes; // [i+0: location, i+1: elements, i+2: type, i+3: normalized, i+4: offset]
	size_t attributes_size;
	GLuint index;
	GLsizei stride;
};

typedef enum _mz_shader_type shader_type;
typedef enum _mz_vertex_attribute_type vertex_attribute_type;
typedef GLuint shader;
typedef GLuint shader_program;
typedef struct _mz_vertex_attribute_buffer vertex_attribute_buffer;

MZ_API shader load_shader_from_string(const char* code, shader_type type);
MZ_API shader load_shader(const char* filename, shader_type type);

// `link_shader_then_delete` recommended, `link_shader` will not delete the shaders after linkage
MZ_API shader_program link_shader(shader vertex, shader fragment);
// Will delete shaders passed in
MZ_API shader_program link_shader_then_delete(shader* vertex, shader* fragment);

MZ_API vertex_attribute_buffer load_vertex_attribute_buffer(shader_program program);
MZ_API void add_vertex_attribute(vertex_attribute_buffer* buffer, const char* attribute, size_t elements, vertex_attribute_type type, size_t type_size, mz_boolean normalized);
MZ_API void enable_vertex_attributes(vertex_attribute_buffer* buffer);
MZ_API void unload_vertex_attribute_buffer(vertex_attribute_buffer* buffer);

// TODO: Uniform upload functions

// Unload shader and set shader to 0
MZ_API void unload_shader(shader* shader);
// Unload shader program and remove all values
MZ_API void unload_shader_program(shader_program* program);

MZ_API void unload_shaders(shader** shaders, size_t length);
MZ_API void unload_shader_programs(shader_program** programs, size_t length);

#endif // MUZZLE_CORE_SHADER_H