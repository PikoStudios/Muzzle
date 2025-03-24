#ifndef MUZZLE_CORE_SHADER_H
#define MUZZLE_CORE_SHADER_H

#include "../backend.h"
#include "applet.h"

typedef enum
{
    SHADER_TYPE_PASS = 0,
    SHADER_TYPE_DIRECT_QUAD = 1,
    SHADER_TYPE_DIRECT_CIRCLE = 2,
    SHADER_TYPE_DIRECT_SPRITE = 3,
    SHADER_TYPE_DIRECT_TEXT = 4
} mz_shader_type;

typedef struct mz_shader
{
    GLuint pid;
    mz_shader_type type;
} mz_shader;

MZ_API mz_shader mz_create_shader(const char* vertex, const char* fragment, mz_shader_type type);
MZ_API mz_shader mz_load_shader(const char* vertex_filepath, const char* fragment_filepath, mz_shader_type type);

MZ_API void mz_use_shader_pass(mz_applet* applet, mz_shader shader);
MZ_API void mz_begin_shader(mz_applet* applet, mz_shader shader);
MZ_API void mz_end_shader(mz_applet* applet, mz_shader shader);

MZ_API void mz_unload_shader(mz_shader shader);

#endif // MUZZLE_CORE_SHADER_H
