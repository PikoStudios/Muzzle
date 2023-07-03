#ifndef MUZZLE_CORE_SHADER_H
#define MUZZLE_CORE_SHADER_H

#include "../backend.h"
#include "Error.h"

enum _mz_shader_type
{
	SHADER_VERTEX=GL_VERTEX_SHADER,
	SHADER_FRAGMENT=GL_FRAGMENT_SHADER
};

typedef enum _mz_shader_type shader_type;
typedef GLuint shader;
typedef GLuint shader_program;

MZ_API shader load_shader_from_string(const char* code, shader_type type);
MZ_API shader load_shader(const char* filename, shader_type type);

// `link_shader_then_delete` recommended, `link_shader` will not delete the shaders after linkage
MZ_API shader_program link_shader(shader vertex, shader fragment);
// Will delete shaders passed in
MZ_API shader_program link_shader_then_delete(shader* vertex, shader* fragment);

// TODO: Uniform upload functions

MZ_API void unload_shader(shader* shader);
MZ_API void unload_shader_program(shader_program* program);

MZ_API void unload_shaders(shader** shaders, size_t length);
MZ_API void unload_shader_programs(shader_program** programs, size_t length);

#endif // MUZZLE_CORE_SHADER_H