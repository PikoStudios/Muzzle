#pragma once
#include "../backend.h"
#include "../core/Error.h"
#include <stdlib.h>

struct __internal_mz_renderer
{
    unsigned int **va;
    unsigned int **vb;
    
    size_t vas;
    size_t vbs;
};

struct __internal_mz_renderer __internal_renderer;

void start_renderer();
void unload_renderer(); // TODO: Handle this in ExitMuzzle() when merging modern pipeline -> legacy