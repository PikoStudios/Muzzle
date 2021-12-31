#pragma once
#include "../backend.h"
#include "../core/Error.h"
#include <stdlib.h>

// TODO: Create all the object types

struct _mz_renderer
{
    unsigned int **va;
    unsigned int **vb;
    
    void **queue;

    size_t vas;
    size_t vbs;
    size_t qs;
};


typedef struct _mz_renderer renderer;

void start_renderer(renderer* renderer);
void unload_renderer(renderer* renderer); // TODO: Handle this in ExitMuzzle() when merging modern pipeline -> legacy

void add_to_renderer(void* object);