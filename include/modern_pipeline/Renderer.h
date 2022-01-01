#pragma once
#include "../backend.h"
#include "../core/Error.h"
#include <stdlib.h>

#define ERROR_MSG_SIZE 1123 // 1024 + 99

// TODO: Create all the object types

static struct _mz_queue_object
{
    void *object;
    int type;
    int draw_type;
    size_t components;
    int type_value;
    size_t size;
};

typedef struct _mz_queue_object queue_object;

struct _mz_renderer
{
    unsigned int **varray;
    unsigned int **buffer;
    
    queue_object **queue;

    size_t varray_s;
    size_t bs;
    size_t qs;
};

typedef struct _mz_renderer renderer; 

void start_renderer(renderer* renderer);
void unload_renderer(renderer* renderer); // TODO: Handle this in ExitMuzzle() when merging modern pipeline -> legacy

void add_to_renderer(renderer* renderer, void* object, int type, int draw_type, size_t components, int type_value, size_t size);
void queue_renderer(renderer* renderer);