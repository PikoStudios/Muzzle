#pragma once
#include "../backend.h"
#include "../modern_pipeline/Shaders.h"
#include "Error.h"
#include "vector.h"
#include "tint.h"

#define MZ_BATCHER_RECTANGLE_VERTEX_SIZE 6
#define MZ_BATCHER_RECTANGLE_VERTICES_QUADS 4
#define MZ_BATCHER_RECTANGLE_VERTEX_POS_SIZE 2
#define MZ_BATCHER_RECTANGLE_VERTEX_POS_OFFSET 0
#define MZ_BATCHER_RECTANGLE_VERTEX_TINT_SIZE 4
#define MZ_BATCHER_RECTANGLE_VERTEX_TINT_OFFSET 8 // pos_offset + pos_size * 4

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
    int vertex_size;
    int vertices_size;
    int object_count;
    int max_size;
    GLuint vao;
    GLuint vbo;
    shader_program global_shader;
};

typedef enum _BATCHER_TYPES BATCHER_TYPES;
typedef struct _batcher batcher;

void draw_batcher(batcher* renderer);

// Rectangle Batch Renderer
batcher create_batcher_rectangle(int max_size);
void push_batcher_rectangle(batcher* renderer, GLfloat x, GLfloat y, GLfloat w, GLfloat h, tint color_drawn);