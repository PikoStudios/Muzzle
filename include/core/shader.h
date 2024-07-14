#ifndef MUZZLE_CORE_SHADER_H
#define MUZZLE_CORE_SHADER_H

#include "../backend.h"
#include "applet.h"

typedef enum
{
    SHADER_TARGET_QUAD = 0,
    SHADER_TARGET_SPRITE = 1,
    SHADER_TARGET_CIRCLE = 2
    // TODO: SHADER_TARGET_ALL
} mz_shader_target;

typedef struct mz_shader
{
    GLuint pid;
    mz_shader_target target;
} mz_shader;

// Create a shader from source strings
MZ_API mz_shader mz_create_shader(const char* vertex_src, const char* fragment_src, mz_shader_target target);
MZ_API int mz_create_shaders(mz_shader* out, size_t out_len, const char** vertex_srcs, size_t vs_len, const char** fragment_srcs, size_t fs_len, mz_shader_target target);

// Load a shader from files
MZ_API mz_shader mz_load_shader(const char* vertex_filepath, const char* fragment_filepath, mz_shader_target target);
MZ_API int mz_load_shaders(mz_shader* out, size_t out_len, const char** vertex_filepaths, size_t vf_len, const char** fragment_filepaths, size_t ff_len, mz_shader_target target);

MZ_API void mz_use_shader(mz_applet* applet, mz_shader shader);
MZ_API void mz_use_shaders(mz_applet* applet, mz_shader* shaders, size_t shaders_len);

MZ_API void mz_unload_shader(mz_shader shader);
MZ_API void mz_unload_shaders(mz_shader* shaders, size_t len);

#endif // MUZZLE_CORE_SHADER_H
