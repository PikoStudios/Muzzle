#pragma once
#include "../backend.h"
#include "../core/tint.h"
#include "../core/Error.h"
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

MZ_API shader load_shader(shader_type type, const char* filepath);
MZ_API shader_program link_shader(shader vertex, shader fragment);

MZ_API void load_shader_program(shader_program shader);
MZ_API void unload_shader_program(shader_program shader);
MZ_API void clear_shader_program();