#include "core/Batcher.h"

batcher load_batcher(int type, int max_size)
{
    switch(type)
    {
    case BATCHER_TYPE_QUAD:
        return _mz_internal_init_batcher_rect(max_size);
        break;
    case BATCHER_TYPE_CIRCLE:
        log_status(STATUS_FATAL_ERROR, "Batcher type 'BATCHER_TYPE_CIRCLE' not implemented!");
        break;
    case BATCHER_TYPE_LINE:
        log_status(STATUS_FATAL_ERROR, "Batcher type 'BATCHER_TYPE_LINE' not implemented!");
        break;
    default:
        log_status(STATUS_FATAL_ERROR, "Unknown batcher type");
        break;
    }
}

static batcher _mz_internal_init_batcher_rect(int max_size)
{   
    batcher temp;
    temp.batch_shader = 0;
    temp.vertices_index = 0;
    temp.texture_index = 1;
    temp.max_size = max_size;

    temp.vertex_size = sizeof(struct _quad_vertex);
    temp.vertices = MZ_CALLOC(max_size * 4, temp.vertex_size);

    if (temp.vertices == NULL) log_status(STATUS_FATAL_ERROR, "Failed to allocate memory for Batch Renderer");

    glGenVertexArrays(1, &temp.vao);
    glBindVertexArray(temp.vao);

    glGenBuffers(1, &temp.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, temp.vbo);
    glBufferData(GL_ARRAY_BUFFER, (temp.vertex_size * 4) * max_size, NULL, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &temp.ebo);
    int indices[6 * max_size];

    for (int i = 0; i < max_size; i++)
    {
        int index_offset = 6 * i;
        int offset = 4 * i;

        // Triangle 1
        indices[index_offset] = offset + 3;
        indices[index_offset + 1] = offset + 2;
        indices[index_offset + 2] = offset;

        // Triangle 2
        indices[index_offset + 3] = offset;
        indices[index_offset + 4] = offset + 2;
        indices[index_offset + 5] = offset + 1;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, temp.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * max_size, indices, GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(temp.vbo, 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, temp.vertex_size, (void*)(offsetof(struct _quad_vertex, position)));
    
    glEnableVertexArrayAttrib(temp.vbo, 1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, temp.vertex_size, (void*)(offsetof(struct _quad_vertex, color_drawn)));
    
    glEnableVertexArrayAttrib(temp.vbo, 2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, temp.vertex_size, (void*)(offsetof(struct _quad_vertex, tex_coords)));
    
    glEnableVertexArrayAttrib(temp.vbo, 3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, temp.vertex_size, (void*)(offsetof(struct _quad_vertex, tex_id)));
    
    log_status(STATUS_SUCCESS, "Created Rectangle Batcher");

    return temp;
}

void draw_batcher(batcher* renderer)
{
    // Not fastest way to do this, but still way faster than indiviual draw calls
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(struct _quad_vertex), renderer->vertices);

    attach_shader_program(renderer->batch_shader);
    
    glBindVertexArray(renderer->vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glDrawElements(GL_TRIANGLES, renderer->vertices_index * 6, GL_UNSIGNED_INT, 0);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);

    detach_shader_program(renderer->batch_shader);
}

void update_batcher_rectangle(batcher* renderer, unsigned int index, GLfloat x, GLfloat y, GLfloat w, GLfloat h, tint color_drawn)
{
    int offset = (index * 4) * MZ_BATCHER_RECTANGLE_VERTEX_SIZE;
    int offset_two = offset + MZ_BATCHER_RECTANGLE_VERTEX_SIZE;
    int offset_three = offset + (MZ_BATCHER_RECTANGLE_VERTEX_SIZE * 2);
    int offset_four = offset + (MZ_BATCHER_RECTANGLE_VERTEX_SIZE * 3);
    
    

    // Load Vertex data
    renderer->vertices[index] 
    renderer->vertices[offset] = x + w;
    renderer->vertices[offset + 1] = y + h;
    renderer->vertices[offset + 2] = color_drawn.r;
    renderer->vertices[offset + 3] = color_drawn.g;
    renderer->vertices[offset + 4] = color_drawn.b;
    renderer->vertices[offset + 5] = color_drawn.a;

    renderer->vertices[offset_two] = x + w;
    renderer->vertices[offset_two + 1] = y;
    renderer->vertices[offset_two + 2] = color_drawn.r;
    renderer->vertices[offset_two + 3] = color_drawn.g;
    renderer->vertices[offset_two + 4] = color_drawn.b;
    renderer->vertices[offset_two + 5] = color_drawn.a;
    
    renderer->vertices[offset_three] = x;
    renderer->vertices[offset_three + 1] = y;
    renderer->vertices[offset_three + 2] = color_drawn.r;
    renderer->vertices[offset_three + 3] = color_drawn.g;
    renderer->vertices[offset_three + 5] = color_drawn.a;
    renderer->vertices[offset_three + 4] = color_drawn.b;

    renderer->vertices[offset_four] = x;
    renderer->vertices[offset_four + 1] = y + h;
    renderer->vertices[offset_four + 2] = color_drawn.r;
    renderer->vertices[offset_four + 3] = color_drawn.g;
    renderer->vertices[offset_four + 4] = color_drawn.b;
    renderer->vertices[offset_four + 5] = color_drawn.a;
}

void push_batcher_rectangle(batcher* renderer, GLfloat x, GLfloat y, GLfloat w, GLfloat h, tint color_drawn)
{
    if (renderer->vertices_index + 1 > renderer->max_size)
    {
        log_status(STATUS_ERROR, "Batcher overflow! Cannot push rectangle to batcher");
        return;
    }

    int index = renderer->vertices_index++;
    update_batcher_rectangle(renderer, index, x, y, w, h, color_drawn);
}

void unload_batcher(batcher* renderer)
{
    glDeleteVertexArrays(1, &renderer->vao);
    glDeleteBuffers(1, &renderer->vbo);
    glDeleteBuffers(1, &renderer->ebo);
    
    MZ_FREE(renderer->vertices);
}