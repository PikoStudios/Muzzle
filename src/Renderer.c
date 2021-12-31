#include "modern_pipeline/Renderer.h"

void start_renderer(renderer* renderer)
{
    renderer->vas = 1;
    renderer->va = MZ_CALLOC(1, sizeof(unsigned int*));

    if (renderer->va == NULL)
        log_status(STATUS_FATAL_ERROR, "Failed to allocate enough memory for renderer [VA] (DANGEROUS MODERN PIPELINE ENABLED)");
    
    renderer->va[0] = NULL;

    renderer->vbs = 1;
    renderer->vb = MZ_CALLOC(1, sizeof(unsigned int*));

    if (renderer->vb == NULL)
        log_status(STATUS_FATAL_ERROR, "Failed to allocate enough memory for renderer [VB] (DANGEROUS MODERN PIPELINE ENABLED)");

    renderer->vb[0] = NULL;

    renderer->qs = 1;
    renderer->queue = MZ_MALLOC(sizeof(queue_object*));

    if (renderer->queue == NULL)
        log_status(STATUS_FATAL_ERROR, "Failed to allocate enough memory for renderer queue (DANGEROUS MODERN PIPELINE ENABLED)");
    
    renderer->queue[0] = MZ_MALLOC(sizeof(queue_object*));

    if (renderer->queue[0] == NULL)
        log_status(STATUS_FATAL_ERROR, "Failed to allocate enough memory for renderer queue [slot 0] (DANGEROUS MODERN PIPELINE ENABLED)");

    renderer->queue[0] = MUZZLE_NULL;
}

void unload_renderer(renderer* renderer)
{
    for (int i = 0; i < renderer->vas; i++)
    {
        (!renderer->va[i] == NULL) ? MZ_FREE(renderer->va[i]) : NULL;
    }
    MZ_FREE(renderer->va);

    for (int i = 0; i < renderer->vbs; i++)
    {
        (!renderer->vb[i] == NULL) ? MZ_FREE(renderer->vb[i]) : NULL;
    }
    MZ_FREE(renderer->vb);

    for (int i = 0; i < renderer->qs; i++)
    {
        MZ_FREE(renderer->queue[i]);
    }
    MZ_FREE(renderer->queue);
}

void add_to_renderer(renderer* renderer, void* object, int type, int draw_type)
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

    renderer->queue[new] = MZ_MALLOC(sizeof(queue_object*));

    if (renderer->queue[new] == NULL)
    {
        char msg[ERROR_MSG_SIZE];
        sprintf(msg, "Failed to allocate enough memory for renderer queue [slot %d] (DANGEROUS MODERN PIPELINE ENABLED)");
        log_status(STATUS_FATAL_ERROR, msg);
    }

    renderer->queue[new]->draw_type = draw_type;
    renderer->queue[new]->type = type;
    renderer->queue[new]->object = object;
}

// STREAM NOTE: Done off stream
void queue_renderer(renderer* renderer)
{
    if (renderer->queue[0] == MUZZLE_NULL) return;
    
    glGenVertexArrays(renderer->vas, &renderer->va);
    glGenBuffers(renderer->vbs, &renderer->vb);
    
    glBindVertexArray(renderer->va);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vb);

    for (int i = 0; i < renderer->qs; i++)
    {
        if (renderer->queue[i] == NULL)
        {
            log_status(STATUS_ERROR, "Corrupted/Invalid object found in queue (DANGEROUS MODERN PIPELINE ENABLED)");
            break;
        }

        glBufferData(renderer->queue[i]->type, sizeof(renderer->queue[i]->object), renderer->queue[i]->object, renderer->queue[i]->draw_type);
    }
    
}