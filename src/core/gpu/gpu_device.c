#include "core/gpu/gpu_device.h"
#include "backend.h"
#include "core/logging.h"
#include "core/memory.h"
#include <stdint.h>
#include <string.h>

mz_gpu_device mz_gpu_create_device(void)
{
    MZ_TRACK_FUNCTION();

    mz_gpu_device device = (mz_gpu_device){0};

    device.handles_capacity = MUZZLE_GPU_DEVICE_HANDLES_INITIAL_CAPACITY;
    device.handles_size = 0;
    device.handles = MZ_MALLOC(sizeof(uintptr_t) * device.handles_capacity);

    device.handles_free_list = MZ_MALLOC(sizeof(uint32_t) * device.handles_capacity);
    device.handles_free_list_size = device.handles_capacity;

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
    gpu->handles_size = 0;
    gpu->handles_capacity = 0;

    gpu->handles_free_list = NULL;
    gpu->handles_free_list_size = 0;
}

uintptr_t mz_gpu_append_handle(mz_gpu_device* gpu, uintptr_t handle)
{
    MZ_TRACK_FUNCTION();

    if (gpu->handles_size == gpu->handles_capacity)
    {
        const size_t old_capacity = gpu->handles_capacity;
        gpu->handles_capacity *= MUZZLE_GPU_DEVICE_HANDLES_GROWTH_FACTOR;
        const size_t capacity_diff = gpu->handles_capacity - old_capacity;
         
        gpu->handles = MZ_REALLOC(gpu->handles, gpu->handles_capacity * sizeof(uintptr_t));
        gpu->handles_free_list = MZ_REALLOC(gpu->handles_free_list, gpu->handles_capacity * sizeof(uint32_t));
        gpu->handles_free_list_size += capacity_diff; // Preparing to shift existing data to the right, so we increase our size by how much we added

        if (gpu->handles == NULL || gpu->handles_free_list == NULL)
        {
            mz_log_status(LOG_STATUS_FATAL_ERROR, "Failed to reallocate GPU device handles buffer");
        }

        // TODO: is this doing what i want it to? Test!
        memmove(gpu->handles_free_list + capacity_diff, gpu->handles_free_list, old_capacity * sizeof(uint32_t));

        for (int i = 0; i < capacity_diff; i++)
        {
            gpu->handles_free_list[i] = gpu->handles_capacity - i - 1;
        }
    }

    const uintptr_t idx = gpu->handles_free_list[--gpu->handles_free_list_size];
    gpu->handles[idx] = handle;

    return idx;
}

void mz_gpu_remove_handle(mz_gpu_device* gpu, uintptr_t handle)
{
    MZ_TRACK_FUNCTION();

    gpu->handles[handle] = 0;
    gpu->handles_free_list[gpu->handles_free_list_size++] = handle;

    // TODO: Test!!!!
    MZ_ASSERT_DETAILED(gpu->handles_free_list_size + 1 < gpu->handles_capacity, "Handles free list size should never exceed handles capacity");
}
