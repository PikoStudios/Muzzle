#include "modern_pipeline/Renderer.h"

void start_renderer(renderer* renderer)
{
    renderer->varray_s = 1;
    renderer->varray = MZ_CALLOC(1, sizeof(unsigned int));

    if (renderer->varray == NULL)
        log_status(STATUS_FATAL_ERROR, "Failed to allocate enough memory for renderer [VA] (DANGEROUS MODERN PIPELINE ENABLED)");
    
    renderer->varray[0] = NULL;

    renderer->vbs = 1;
    renderer->buffer = MZ_CALLOC(1, sizeof(unsigned int));

    if (renderer->buffer == NULL)
        log_status(STATUS_FATAL_ERROR, "Failed to allocate enough memory for renderer [VB] (DANGEROUS MODERN PIPELINE ENABLED)");

    renderer->buffer[0] = NULL;

    renderer->qs = 1;
    renderer->queue = MZ_MALLOC(sizeof(queue_object));

    if (renderer->queue == NULL)
        log_status(STATUS_FATAL_ERROR, "Failed to allocate enough memory for renderer queue (DANGEROUS MODERN PIPELINE ENABLED)");

    renderer->queue[0] = MUZZLE_NULL;
}

void unload_renderer(renderer* renderer)
{
    MZ_FREE(renderer->varray);
    MZ_FREE(renderer->buffer);
    MZ_FREE(renderer->queue);
}

void add_to_renderer(renderer* renderer, void* object, int type, int draw_type, size_t components, int type_value, size_t size)
{
    if (renderer->queue[0] == MUZZLE_NULL)
    {
        renderer->queue[0] = object;
        return;
    }

    size_t new = renderer->qs;

    renderer->qs++;
    renderer->queue = MZ_REALLOC(renderer->queue, sizeof(queue_object*) * renderer->qs);

    if (renderer->queue == NULL)
        log_status(STATUS_FATAL_ERROR, "Failed to reallocate enough memory for renderer queue (DANGEROUS MODERN PIPELINE ENABLED)");

    renderer->queue[new]->draw_type = draw_type;
    renderer->queue[new]->type = type;
    renderer->queue[new]->object = object;
    renderer->queue[new]->type_value = type_value;
    renderer->queue[new]->components = components;
    renderer->queue[new]->size = size;
}

void queue_renderer(renderer* renderer)
{
    if (renderer->queue[0] == MUZZLE_NULL) return;
    
    glGenVertexArrays(renderer->varray_s, &renderer->varray);
    glGenBuffers(renderer->vbs, &renderer->buffer);
    
    glBindVertexArray(renderer->varray);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->buffer);

    for (int i = 0; i < renderer->qs; i++)
    {
        if (renderer->queue[i] == NULL)
        {
            log_status(STATUS_ERROR, "Corrupted/Invalid object found in queue (DANGEROUS MODERN PIPELINE ENABLED)");
            break;
        }

        glBufferData(renderer->queue[i]->type, sizeof(renderer->queue[i]->object), renderer->queue[i]->object, renderer->queue[i]->draw_type);
        glVertexAttribPointer(0, renderer->queue[i]->components, renderer->queue[i]->type_value, GL_FALSE, renderer->queue[i]->size, NULL);
    }

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}