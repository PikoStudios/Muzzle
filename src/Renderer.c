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
}