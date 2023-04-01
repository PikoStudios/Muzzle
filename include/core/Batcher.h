#pragma once
#include "../backend.h"
#include "../modern_pipeline/Shaders.h"
#include "Error.h"
#include "vector.h"
#include "tint.h"
#include <stdint.h>
#include <stddef.h>

// shoutout to the cherno

#define MZ_BATCHER_RECTANGLE_VERTEX_SIZE 6
#define MZ_BATCHER_RECTANGLE_VERTICES_QUADS 4
#define MZ_BATCHER_RECTANGLE_VERTEX_POS_SIZE 2
#define MZ_BATCHER_RECTANGLE_VERTEX_POS_OFFSET 0
#define MZ_BATCHER_RECTANGLE_VERTEX_TINT_SIZE 4
#define MZ_BATCHER_RECTANGLE_VERTEX_TINT_OFFSET 8 // pos_offset + pos_size * 4


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

enum _BATCHER_TYPES
{
    BATCHER_TYPE_QUAD = 0,
    BATCHER_TYPE_CIRCLE,
    BATCHER_TYPE_LINE,
};

struct _batcher
{
    struct _vertex* vertices;
    struct _vertex* vertices_ptr;
    size_t vertices_size;
    uint32_t vertices_index;
    size_t vertex_size;
    size_t max_size;
    uint32_t* textures;
    uint32_t texture_index;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    shader_program batch_shader;
};

struct _batch
{
    struct _batcher* quads;
    struct _batcher* quads_ptr;
    size_t quads_size;
};

typedef enum _BATCHER_TYPES BATCHER_TYPES;
typedef struct _batcher batcher;
typedef struct _batch batch;

// NOTE: Not calling it "draw_batcher" because this function should not be seen easily.
// NOTE: Not using internal naming convention because this function could reasonably be used
// NOTE: Outside of an internal space
MZ_API void next_frame_batcher(int type, batcher* renderer);

// Internal Batcher Initialization functions //
// TODO: Find better name :)
static batcher _mz_internal_init_batcher_rect(int max_size);

// Public batcher initialization function //
MZ_API batcher load_batcher(int type, int max_size);

MZ_API void update_batcher_rectangle(batcher* renderer, unsigned int index, GLfloat x, GLfloat y, GLfloat w, GLfloat h, tint color_drawn);
MZ_API void push_batcher_rectangle(batcher* renderer, GLfloat x, GLfloat y, GLfloat w, GLfloat h, tint color_drawn);

MZ_API void unload_batcher(batcher* renderer);