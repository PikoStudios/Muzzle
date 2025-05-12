#ifndef MUZZLE_CORE_SHADER_H
#define MUZZLE_CORE_SHADER_H

#include "../backend.h"
#include "applet.h"
#include <stdint.h>

typedef enum
{
    SHADER_TYPE_PASS = 0,
    SHADER_TYPE_DIRECT_QUAD = 1,
    SHADER_TYPE_DIRECT_CIRCLE = 2,
    SHADER_TYPE_DIRECT_SPRITE = 3,
    SHADER_TYPE_DIRECT_TEXT = 4
} mz_shader_type;

typedef enum
{
    SHADER_COMPONENT_TYPE_VERTEX = GL_VERTEX_SHADER,
    SHADER_COMPONENT_TYPE_FRAGMENT = GL_FRAGMENT_SHADER,
    SHADER_COMPONENT_TYPE_GEOMETRY = GL_GEOMETRY_SHADER,
} mz_shader_component_type;


typedef enum
{
    SHADER_COMPONENT_VERTEX_PRIMITIVE_TYPE_TRIANGLE = GL_TRIANGLES,
    SHADER_COMPONENT_VERTEX_PRIMITIVE_TYPE_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    SHADER_COMPONENT_VERTEX_PRIMITIVE_TYPE_POINT = GL_POINTS
} mz_shader_component_vertex_primitive_type;

typedef enum
{
    SHADER_COMPONENT_SOURCE_TYPE_FILEPATH = 0,
    SHADER_COMPONENT_SOURCE_TYPE_SOURCE_CODE = 1
} mz_shader_component_source_type;

typedef struct mz_shader
{
    GLuint pid;
    mz_shader_type type;
} mz_shader;

typedef struct mz_shader_component_vertex_attribute
{

} mz_shader_component_vertex_attribute;


typedef struct mz_shader_component
{
    mz_shader_component_type component_type;
    mz_shader_component_source_type source_type;
    const char* source;

    struct
    {
        mz_shader_component_vertex_primitive_type primitive_type;
        mz_shader_component_vertex_attribute* attributes;
        float* vertices;
        size_t attributes_size;
        size_t vertices_size;
    } vertex_metadata;
} mz_shader_component;

typedef struct mz_shader_pipeline
{
    mz_shader_component* components;
    size_t size;
} mz_shader_pipeline;

/*
 *
 * mz_shader_component vertex_shader = (mz_shader_component)
 * {
 *      .component_type = SHADER_COMPONENT_TYPE_VERTEX,
 *      .metadata.vertex =
 *      {
 *          .primitive_type = SHADER_COMPONENT_PRIMITIVE_TYPE_POINT,
 *          .attributes = attr;
 *          .attributes_size = attr_size;
 *          .vertices = data;
 *          .vertices_size = vertices_size;
 *      },
 *      .source_type = SHADER_COMPONENT_SOURCE_TYPE_FILEPATH,
 *      .source = "vert.glsl"
 * };
 *
 * mz_shader_component fragment_shader = (mz_shader_component)
 * {
 *      .component_type = SHADER_COMPONENT_TYPE_FRAGMENT,
 *      .source_type = SHADER_COMPONENT_SOURCE_TYPE_FILEPATH,
 *      .source = "frag.glsl"
 * };
 *
 * mz_shader_component components[] = {vertex_shader, fragment_shader};
 *
 * mz_shader_pipeline pipeline = (mz_shader_pipeline)
 * {
 *      .components = components,
 *      .size = ARRSIZE(components)
 * };
 *
 * mz_shader shader = mz_create_shader_from_pipeline(pipeline);
 */

typedef struct mz_shader_buffer
{
    GLuint id;
    GLuint index;
} mz_shader_buffer;

MZ_API mz_shader mz_create_shader(const char* vertex, const char* fragment, mz_shader_type type);
MZ_API mz_shader mz_load_shader(const char* vertex_filepath, const char* fragment_filepath, mz_shader_type type);

MZ_API mz_shader mz_create_shader_from_pipeline(mz_shader_pipeline pipeline);

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

MZ_API mz_shader_buffer mz_create_shader_buffer(int index, void* data, size_t size);
MZ_API void mz_realloc_shader_buffer(mz_shader_buffer buffer, void* data, size_t size);
MZ_API void mz_upload_shader_buffer(mz_shader_buffer buffer, intptr_t offset, void* data, size_t size);
MZ_API void mz_unload_shader_buffer(mz_shader_buffer buffer);

#endif // MUZZLE_CORE_SHADER_H
