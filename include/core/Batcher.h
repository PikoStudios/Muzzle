#pragma once
#include "../backend.h"
#include "../modern_pipeline/Shaders.h"
#include "Error.h"
#include "vector.h"
#include "tint.h"
#include <stdint.h>
#include <stddef.h>

/* Vertex Definition:
 struct vertex
 {
     vec3 position;
     vec4 color;
     vec2 tex_coords;
     float tex_index;   
 }
*/

// Internal vertex structures
struct _quad_vertex
{
    vec3 position;
    tint_f color_drawn;
    vec2 tex_coords;
    float tex_id;
};

struct _circle_vertex
{
    vec3 world_position;
    vec3 local_position;
    tint color_drawn;
    float thickness;
    float fade;
};

struct _line_vertex
{
    vec3 position;
    tint_f color_drawn;
};

struct _batcher
{
    uint32_t max_size;
    struct _quad_vertex* quads;
    struct _quad_vertex* quads_current_ptr;
    uint32_t quads_current_index;
    size_t quads_size;
    size_t quads_count;
    shader_program quad_shader;
    GLuint* quads_buffers;
    struct _circle_vertex* circles;
    struct _circle_vertex* circles_current_ptr;
    uint32_t circles_current_index;
    size_t circles_size;
    size_t circles_count;
    shader_program circle_shader;
    GLuint* circles_buffers;
    struct _line_vertex* lines;
    struct _line_vertex* lines_current_ptr;
    uint32_t lines_currrent_index;
    size_t lines_size;
    size_t lines_count;
    shader_program line_shader;
    GLuint* lines_buffers;
    uint32_t* textures;
    uint32_t texture_index;
    size_t _batch_array_index; // Internal use variable, only used for the first element in an array of batchers
};

typedef struct _batcher batcher;

// NOTE: Automatically called by Muzzle at the during each frame.
MZ_API void update_individual_batcher(batcher* batch);
MZ_API void update_batcher(batcher* batch);

MZ_API batcher load_individual_batcher(int max_size);
MZ_API batcher* load_batcher(int max_size);
MZ_API void unload_individual_batcher(batcher* batch);
MZ_API void unload_batcher(batcher* batch);