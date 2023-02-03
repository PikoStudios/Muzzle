#include "core/Batcher.h"

batcher create_batcher_rectangle(int max_size)
{
    batcher temp;
    temp.global_shader = 0;
    temp.object_count = 0;
    temp.max_size = max_size;

    temp.vertex_size = MZ_BATCHER_RECTANGLE_VERTEX_SIZE;
    temp.vertices_size = (max_size * MZ_BATCHER_RECTANGLE_VERTICES_QUADS) * temp.vertex_size;
    
    // TODO: is it better to call calloc on this or just do temp.vertices[temp.vertices_size]?
    temp.vertices = MZ_CALLOC(temp.vertices_size, sizeof(GLfloat));

    if (temp.vertices == NULL) log_status(STATUS_FATAL_ERROR, "Failed to allocate memory for Batch Renderer");

    glGenVertexArrays(1, &temp.vao);
    glBindVertexArray(temp.vao);

    glGenBuffers(1, &temp.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, temp.vbo);
    glBufferData(GL_ARRAY_BUFFER, temp.vertices_size * 4, NULL, GL_DYNAMIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * max_size, indices, GL_STATIC_DRAW);

    // TODO: I feel like this prolly would not work, so make sure to test this
    glVertexAttribPointer(0, MZ_BATCHER_RECTANGLE_VERTEX_POS_SIZE, GL_FLOAT, 0, MZ_BATCHER_RECTANGLE_VERTEX_SIZE * 4, (GLvoid*)(MZ_BATCHER_RECTANGLE_VERTEX_POS_OFFSET));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, MZ_BATCHER_RECTANGLE_VERTEX_TINT_SIZE, GL_FLOAT, 0, MZ_BATCHER_RECTANGLE_VERTEX_SIZE * 4, (GLvoid*)(MZ_BATCHER_RECTANGLE_VERTEX_TINT_OFFSET));
    glEnableVertexAttribArray(1);

    return temp;
}

void draw_batcher(batcher* renderer)
{
    // Not fastest way to do this, but still way faster than indiviual draw calls
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, renderer->vertices_size, renderer->vertices);

    attach_shader_program(renderer->global_shader);
    
    glDrawElements(GL_TRIANGLES, renderer->object_count * 6, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);

    detach_shader_program(renderer->global_shader);
}

void update_batcher_rectangle(batcher* renderer, unsigned int index, GLfloat x, GLfloat y, GLfloat w, GLfloat h, tint color_drawn)
{
    int offset = (index * 4) * MZ_BATCHER_RECTANGLE_VERTEX_SIZE;
    int offset_two = offset + MZ_BATCHER_RECTANGLE_VERTEX_SIZE;
    int offset_three = offset + (MZ_BATCHER_RECTANGLE_VERTEX_SIZE * 2);
    int offset_four = offset + (MZ_BATCHER_RECTANGLE_VERTEX_SIZE * 3);

    // Load Vertex data
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
    if (renderer->object_count + 1 > renderer->max_size)
    {
        log_status(STATUS_ERROR, "Batcher overflow! Cannot push rectangle to batcher");
        return;
    }

    int index = renderer->object_count++;
    update_batcher_rectangle(renderer, index, x, y, w, h, color_drawn);
}

void unload_batcher(batcher* renderer)
{
    free(renderer->vertices);
}