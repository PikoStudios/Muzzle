#pragma once
#include "../backend.h"
#include "../core/tint.h"
#include "../core/Error.h"
#include "../core/vector.h"
#include "../core/matrix.h"

#include <stdio.h>
#include <stdlib.h>

enum _mz_shader_type
{
    SHADER_FRAGMENT = GL_FRAGMENT_SHADER,
    SHADER_VERTEX = GL_VERTEX_SHADER,
    SHADER_TESS_CONTROL = GL_TESS_CONTROL_SHADER,
    SHADER_TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
    SHADER_GEOMETRY = GL_GEOMETRY_SHADER,
    SHADER_COMPUTE = GL_COMPUTE_SHADER,
};

typedef enum _mz_shader_type shader_type;
typedef GLuint shader;
typedef GLuint shader_program;

MZ_API shader load_shader_from_string(shader_type type, const char* shader_code);
MZ_API shader load_shader(shader_type type, const char* filepath);

// Unrecommended, remember to delete shaders when done
MZ_API shader_program link_shader(shader vertex, shader fragment);

// Recommended function, saves memory
MZ_API shader_program link_shader_then_delete(shader* vertex, shader* fragment);

MZ_API void upload_shader_int(shader_program program, const char* var, int value);
MZ_API void upload_shader_float(shader_program program, const char* var, float value);
MZ_API void upload_shader_vec2(shader_program program, const char* var, vec2 value);
MZ_API void upload_shader_vec3(shader_program program, const char* var, vec3 value);
MZ_API void upload_shader_vec4(shader_program program, const char* var, vec4 value);
MZ_API void upload_shader_mat3(shader_program program, const char* var, mat3 value);
MZ_API void upload_shader_mat4(shader_program program, const char* var, mat4 value);

MZ_API void begin_shader_program(shader_program shader);
MZ_API void end_shader_program();

MZ_API void unload_shader_program(shader_program* shader);
MZ_API void unload_shader(shader* shader);