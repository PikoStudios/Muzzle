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

MZ_API void mz_upload_uniform_int(mz_shader shader, const char* uniform, int value);
MZ_API void mz_upload_uniform_float(mz_shader shader, const char* uniform, float value);
MZ_API void mz_upload_uniform_vec2(mz_shader shader, const char* uniform, mz_vec2 value);
MZ_API void mz_upload_uniform_vec3(mz_shader shader, const char* uniform, mz_vec3 value);
MZ_API void mz_upload_uniform_vec4(mz_shader shader, const char* uniform, mz_vec4 value);

// TODO: Make matrix type
MZ_API void mz_upload_uniform_mat3(mz_shader shader, const char* uniform, const float* matrix);
MZ_API void mz_upload_uniform_mat4(mz_shader shader, const char* uniform, const float* matrix);

#endif // MUZZLE_CORE_SHADER_H
