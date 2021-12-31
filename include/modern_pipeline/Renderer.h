#pragma once
#include "../backend.h"
#include "../core/Error.h"
#include <stdlib.h>

struct _mz_renderer
{
    unsigned int **va;
    unsigned int **vb;
    
    size_t vas;
    size_t vbs;
};

typedef struct _mz_renderer renderer;

void start_renderer(renderer* renderer);
void unload_renderer(renderer* renderer); // TODO: Handle this in ExitMuzzle() when merging modern pipeline -> legacy