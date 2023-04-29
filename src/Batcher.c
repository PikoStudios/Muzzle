#include "core/Batcher.h"
#define VAO(x) x[0]
#define VBO(x) x[1]
#define EBO(x) x[2]

batcher load_individual_batcher(int max_size)
{
    batcher temp;
    temp.max_size = max_size;
    
    temp.textures = MZ_CALLOC(32, sizeof(uint32_t));
    temp.texture_index = 1;
    temp.quads_buffers = MZ_CALLOC(3, sizeof(GLuint));
    temp.circles_buffers = NULL;
    temp.lines_buffers = NULL;
    temp.quads_current_index = 0;
    temp.quads_count = 0;
    temp.circles_current_index = 0;
    temp.circles_count = 0;
    temp.lines_currrent_index = 0;
    temp.lines_count = 0;
    temp.quads = MZ_CALLOC(max_size * 4, sizeof(struct _quad_vertex));
    temp.circles = NULL;
    temp.lines = NULL;
    
    int* quad_indices = MZ_CALLOC(6 * max_size, sizeof(int));
    int* circle_indices = NULL;
    int* lines_indices = NULL;
    
    if (temp.textures == NULL) log_status(STATUS_FATAL_ERROR, "Failed to allocate memory for texture array");
    if (temp.quads_buffers == NULL) log_status(STATUS_FATAL_ERROR, "Failed to allocate memory for quad buffers");
    if (temp.quads == NULL) log_status(STATUS_FATAL_ERROR, "Failed to allocate memory for quad array");
    if (quad_indices == NULL) log_status(STATUS_FATAL_ERROR, "Failed to allocate memory for quad indices");
    
    temp.quads_current_ptr = &temp.quads[0];
    
    glGenVertexArrays(1, &VAO(temp.quads_buffers));
    glBindVertexArray(VAO(temp.quads_buffers));
    
    glGenBuffers(1, &VBO(temp.quads_buffers));
    glBindBuffer(GL_ARRAY_BUFFER, VBO(temp.quads_buffers));
    glBufferData(GL_ARRAY_BUFFER, (sizeof(struct _quad_vertex) * 4) * max_size, NULL, GL_DYNAMIC_DRAW);
    
    glGenBuffers(1, &EBO(temp.quads_buffers));
    
    for (int i = 0; i < max_size; i++)
    {
        int index_offset = 6 * i;
        int offset = 4 * i;
        
        // Triangle 1
        quad_indices[index_offset++] = offset + 3;
        quad_indices[index_offset++] = offset + 2;
        quad_indices[index_offset++] = offset;
        
        // Triangle 2
        quad_indices[index_offset++] = offset;
        quad_indices[index_offset++] = offset + 2;
        quad_indices[index_offset++] = offset + 1;
    }
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO(temp.quads_buffers));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * max_size, quad_indices, GL_STATIC_DRAW);
    
    glEnableVertexArrayAttrib(VAO(temp.quads_buffers), 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct _quad_vertex), (void*)(offsetof(struct _quad_vertex, position)));
    
    glEnableVertexArrayAttrib(VAO(temp.quads_buffers), 1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(struct _quad_vertex), (void*)(offsetof(struct _quad_vertex, color_drawn)));
    
    glEnableVertexArrayAttrib(VAO(temp.quads_buffers), 2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct _quad_vertex), (void*)(offsetof(struct _quad_vertex, tex_coords)));
    
    glEnableVertexArrayAttrib(VAO(temp.quads_buffers), 3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(struct _quad_vertex), (void*)(offsetof(struct _quad_vertex, tex_id)));
    
    MZ_FREE(quad_indices);
    
    uint32_t* default_texture = &temp.textures[0];
    uint32_t default_texture_hex = 0xFFFFFFFF;
    
    glCreateTextures(GL_TEXTURE_2D, 1, default_texture);
    glTextureStorage2D(*default_texture, 1, GL_RGBA8, 1, 1);
    
    glTextureParameteri(*default_texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(*default_texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(*default_texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(*default_texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTextureSubImage2D(*default_texture, 0, 0, 0, 1, 1, GL_RGBA8, GL_UNSIGNED_BYTE, &default_texture_hex);
    
    return temp;
}

batcher* load_batcher(int max_size)
{
    batcher* temp = MZ_CALLOC(1, sizeof(batcher));
    if (temp == NULL) log_status(STATUS_FATAL_ERROR, "Failed to allocate memory for batcher");
    
    temp[0] = load_individual_batcher(max_size);
    temp[0]._batch_array_index = 1;
    return temp;
}

void update_individual_batcher(batcher* batch)
{
    // TODO: Implement
}

void update_batcher(batcher* batch)
{
    for (int i = 0; i < batch[0]._batch_array_index; i++)
    {
        update_individual_batcher(&batch[i]);
    }
}

void unload_individual_batcher(batcher* batch)
{
    glDeleteVertexArrays(1, &VAO(batch->quads_buffers));
    glDeleteBuffers(1, &VBO(batch->quads_buffers));
    glDeleteBuffers(1, &EBO(batch->quads_buffers));
    glDeleteTextures(batch->texture_index, batch->textures);
    
    // TODO: Unload other buffers
    // TODO: Unload shaders
    
    MZ_FREE(batch->quads);
    MZ_FREE(batch->quads_buffers);
}

void unload_batcher(batcher* batch)
{
    // Skip first element so we can preserve batch array index
    for (int i = 1; i < batch[0]._batch_array_index; i++)
    {
        unload_individual_batcher(&batch[i]);
    }
    
    unload_individual_batcher(&batch[0]);
    MZ_FREE(batch);
}