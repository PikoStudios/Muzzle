#include "modern_pipeline/Renderer.h"

void start_mz_renderer()
{
    __internal_renderer.vas = 1;
    __internal_renderer.va = MZ_CALLOC(1, sizeof(unsigned int*));

    if (__internal_renderer.va == NULL)
        log_status(STATUS_FATAL_ERROR, "Failed to allocate enough memory for renderer [VA] (DANGEROUS MODERN PIPELINE ENABLED)");
    
    __internal_renderer.va[0] = NULL;

    __internal_renderer.vbs = 1;
    __internal_renderer.vb = MZ_CALLOC(1, sizeof(unsigned int*));

    if (__internal_renderer.vb == NULL)
        log_status(STATUS_FATAL_ERROR, "Failed to allocate enough memory for renderer [VB] (DANGEROUS MODERN PIPELINE ENABLED)");

    __internal_renderer.vb[0] = NULL;
}

void unload_renderer()
{
    for (int i = 0; i < __internal_renderer.vas; i++)
    {
        MZ_FREE(__internal_renderer.va[i]);
    }
    MZ_FREE(__internal_renderer.va);

    for (int i = 0; i < __internal_renderer.vbs; i++)
    {
        MZ_FREE(__internal_renderer.vb[i]);
    }
    MZ_FREE(__internal_renderer.vb);
}