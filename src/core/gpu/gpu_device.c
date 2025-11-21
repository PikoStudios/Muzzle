#include "core/gpu/gpu_device.h"
#include "backend.h"
#include "core/logging.h"
#include "core/memory.h"
#include <stdint.h>

mz_gpu_device mz_gpu_create_device(void)
{
    MZ_TRACK_FUNCTION();

    mz_gpu_device device = (mz_gpu_device){0};

    device.handles_capacity = MUZZLE_GPU_DEVICE_HANDLES_INITIAL_CAPACITY;
    device.handles_size = 0;
    device.handles = MZ_MALLOC(sizeof(uintptr_t) * device.handles_capacity);

    device.handles_free_list = MZ_MALLOC(sizeof(uintptr_t) * device.handles_capacity);

    if (device.handles == NULL || device.handles_free_list == NULL)
    {
        mz_log_status(LOG_STATUS_FATAL_ERROR, "Failed to allocate GPU device handles buffer");
    }

    // Initialize free list (LIFO order so populate the list in reverse order in a way the smallest indices come last)

    for (int i = 0; i < device.handles_capacity; i++)
    {
        device.handles_free_list[i] = device.handles_capacity - i - 1;
    }

    return device;
}

void mz_gpu_destroy_device(mz_gpu_device* gpu)
{
    MZ_TRACK_FUNCTION();

    gpu->_destroy_impl(gpu);

    MZ_FREE(gpu->handles);
    MZ_FREE(gpu->handles_free_list);

    gpu->handles = NULL;
    gpu->handles_free_list = NULL;
    gpu->handles_size = 0;
    gpu->handles_capacity = 0;
}

uintptr_t mz_gpu_append_handle(mz_gpu_device* gpu, uintptr_t handle)
{
    MZ_TRACK_FUNCTION();

    if (gpu->handles_size == gpu->handles_capacity)
    {
        gpu->handles_capacity *= MUZZLE_GPU_DEVICE_HANDLES_GROWTH_FACTOR;
        gpu->handles = MZ_REALLOC(gpu->handles, gpu->handles_capacity * sizeof(uintptr_t));

        if (gpu->handles == NULL)
        {
            mz_log_status(LOG_STATUS_FATAL_ERROR, "Failed to reallocate GPU device handles buffer");
        }
    }

    uintptr_t idx = gpu->handles_size;
    gpu->handles[gpu->handles_size++] = handle;

    return idx;
}
