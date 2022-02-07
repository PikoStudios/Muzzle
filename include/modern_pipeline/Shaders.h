#pragma once
#include "../backend.h"
#include "../core/tint.h"
#include "../core/Error.h"
#include "stdio.h"

#define USE_DEFAULT_SHADER ((void*)(0))

enum _mz_shader_type
{
    SHADER_VERTEX,
    SHADER_FRAGMENT
};

struct _mz_shader_def
{
    const char* vertex;
    const char* fragment;
}

typedef enum _mz_shader_type shader_type;
typedef struct _mz_shader_def shader_def;
typedef unsigned int shader;

// Remember to free it :))
shader_def load_as_shader_definition(const char* vs_filepath, const char* fs_filepath);
void unload_shader_definition(shader_def* definition);

shader create_shader(shader_def* definition);
void unload_shader(shader shader);

void enable_shader(shader shader);