#pragma once
#include "../backend.h"
#include "../core/tint.h"
#include "stdio.h"

#define SHADER_SOURCE_SIZE 500

static const char* __internal_muzzle_defaults_shader_vertex_shader_source = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

enum _mz_shader_type
{
    VERTEX_SHADER = 0x8B31,
    FRAGMENT_SHADER = 0x8B30
};

typedef unsigned int shader;
typedef unsigned int shader_context;
typedef enum _mz_shader_type shader_type;


shader_context create_shader_context();

void link_shader(shader_context context, shader shader);
void link_shader_context(shader_context context);

void use_shaders(shader_context context);

shader create_default_vertex_shader();
shader create_default_fragment_shader(tint color_drawn);
shader create_shader(shader_type type, const char* source);

void unload_shader(shader shader);