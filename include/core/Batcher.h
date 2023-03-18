#pragma once
#include "../backend.h"
#include "../modern_pipeline/Shaders.h"
#include "Error.h"
#include "vector.h"
#include "tint.h"
#include <stdint.h>

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

enum _BATCHER_TYPES
{
    BATCHER_TYPE_RECTANGLE = 0,
    BATCHER_TYPE_CIRCLE,
    BATCHER_TYPE_LINE,
    BATCHER_TYPE_SPRITE
};

struct _batcher
{
    GLfloat* vertices;
    GLfloat* vertices_ptr;
    uint32_t* textures;
    uint32_t texture_index;
    size_t vertices_size;
    uint32_t vertices_index;
    size_t vertex_size;
    size_t max_size;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    shader_program batch_shader;
};

struct _batch
{
    struct _batcher* quads_batch;
    struct _batcher* quads_batch_ptr;
};

typedef enum _BATCHER_TYPES BATCHER_TYPES;
typedef struct _batcher batcher;
typedef struct _batch batch;

void draw_batcher(batcher* renderer);

// Rectangle Batch Renderer
batcher initialize_batcher_rectangle(int max_size);
void update_batcher_rectangle(batcher* renderer, unsigned int index, GLfloat x, GLfloat y, GLfloat w, GLfloat h, tint color_drawn);
void push_batcher_rectangle(batcher* renderer, GLfloat x, GLfloat y, GLfloat w, GLfloat h, tint color_drawn);

void unload_batcher(batcher* renderer);