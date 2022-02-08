#pragma once
#include "../backend.h"
#include "../core/tint.h"
#include "../core/Error.h"
#include "stdio.h"

#define USE_DEFAULT_SHADER ((void*)(0))

#define MZ_SHADER_ATTRIB_NAME_POSITION     "vertexPosition"
#define MZ_SHADER_ATTRIB_NAME_TEXCOORD     "vertexTexCoord"
#define MZ_SHADER_ATTRIB_NAME_NORMAL       "vertexNormal"
#define MZ_SHADER_ATTRIB_NAME_COLOR        "vertexColor"
#define MZ_SHADER_ATTRIB_NAME_TANGENT      "vertexTangent"
#define MZ_SHADER_ATTRIB_NAME_TEXCOORD2    "vertexTexCoord2"
#define MZ_SHADER_UNIFORM_NAME_MVP         "mvp"
#define MZ_SHADER_UNIFORM_NAME_VIEW        "matView"
#define MZ_SHADER_UNIFORM_NAME_PROJECTION  "matProjection"
#define MZ_SHADER_UNIFORM_NAME_MODEL       "matModel"
#define MZ_SHADER_UNIFORM_NAME_NORMAL      "matNormal"
#define MZ_SHADER_UNIFORM_NAME_COLOR       "colDiffuse"
#define MZ_SHADER_SAMPLER2D_NAME_TEXTURE0  "texture0"
#define MZ_SHADER_SAMPLER2D_NAME_TEXTURE1  "texture1"
#define MZ_SHADER_SAMPLER2D_NAME_TEXTURE2  "texture2"

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

struct _mz_shader
{
    int *locations;
    unsigned int id;
}

typedef enum _mz_shader_type shader_type;
typedef struct _mz_shader_def shader_def;
typedef struct _mz_shader shader;

// Remember to free it :))
shader_def load_as_shader_definition(const char* vs_filepath, const char* fs_filepath);
void unload_shader_definition(shader_def* definition);

shader create_shader(shader_def* definition);
void unload_shader(shader* shader);

void enable_shader(shader* shader);