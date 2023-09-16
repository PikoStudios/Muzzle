#ifndef MUZZLE_CORE_SHADER_H
#define MUZZLE_CORE_SHADER_H

#include "../backend.h"
#include "Error.h"
#include "vector.h"
#include "matrix.h"

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

MZ_API void upload_uniform_int(shader_program program, const char* uniform, int value);
MZ_API void upload_uniform_float(shader_program program, const char* uniform, float value);
MZ_API void upload_uniform_vec2(shader_program program, const char* uniform, vec2 value);
MZ_API void upload_uniform_vec3(shader_program program, const char* uniform, vec3 value);
MZ_API void upload_uniform_vec4(shader_program program, const char* uniform, vec4 value);
MZ_API void upload_uniform_mat3(shader_program program, const char* uniform, mat3 value);
MZ_API void upload_uniform_mat4(shader_program program, const char* uniform, mat4 value);
// TODO: Implement Matrix uploading

// Unload shader and set shader to 0
MZ_API void unload_shader(shader* shader);
// Unload shader program and remove all values
MZ_API void unload_shader_program(shader_program* program);

MZ_API void unload_shaders(shader** shaders, size_t length);
MZ_API void unload_shader_programs(shader_program** programs, size_t length);

#endif // MUZZLE_CORE_SHADER_H