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
    renderer->queue = MZ_MALLOC(sizeof(void*));

    if (renderer->queue == NULL)
        log_status(STATUS_FATAL_ERROR, "Failed to allocate enough memory for renderer queue (DANGEROUS MODERN PIPELINE ENABLED)");
    
    renderer->queue[0] = MZ_MALLOC(sizeof(void*));

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

void add_to_renderer(renderer* renderer, void* object)
{
    if (renderer->queue[0] == MUZZLE_NULL)
    {
        renderer->queue[0] = object;
        return;
    }

    size_t new = renderer->qs;

    renderer->qs++;
    renderer->queue = MZ_REALLOC(renderer->queue, sizeof(void*) * renderer->qs);

    if (renderer->queue == NULL)
        log_status(STATUS_FATAL_ERROR, "Failed to reallocate enough memory for renderer queue (DANGEROUS MODERN PIPELINE ENABLED)");

    renderer->queue[new] = MZ_MALLOC(sizeof(void*));

    if (renderer->queue[new] == NULL)
    {
        char msg[ERROR_MSG_SIZE];
        sprintf(msg, "Failed to allocate enough memory for renderer queue [slot %d] ((DANGEROUS MODERN PIPELINE ENABLED)");
        log_status(STATUS_FATAL_ERROR, msg);
    }

    renderer->queue[new] = object;
}