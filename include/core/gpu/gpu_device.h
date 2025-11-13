#ifndef MUZZLE_GPU_DEVICE_H
#define MUZZLE_GPU_DEVICE_H

#ifndef MUZZLE_GPU_DEVICE_HANDLES_INITIAL_CAPACITY
    #define MUZZLE_GPU_DEVICE_HANDLES_INITIAL_CAPACITY 256
#endif

#ifndef MUZZLE_GPU_DEVICE_HANDLES_GROWTH_FACTOR
    #define MUZZLE_GPU_DEVICE_HANDLES_GROWTH_FACTOR 2
#endif

#include "../../backend.h"
#include "gpu_buffer.h"
#include <stdint.h>

typedef struct mz_gpu_device
{
    void* impl_data;

    uintptr_t* handles;
    size_t handles_size;
    size_t handles_capacity;

    // BUFFERS //
    mz_gpu_buffer (*create_buffer)(struct mz_gpu_device* gpu, size_t size, mz_gpu_buffer_usage usage);
    void (*destroy_buffer)(struct mz_gpu_device* gpu, mz_gpu_buffer* buffer);
    void (*allocate_buffer)(struct mz_gpu_device* gpu, mz_gpu_buffer* buffer, const void* data);
    void* (*update_buffer)(struct mz_gpu_device* gpu, mz_gpu_buffer* buffer, size_t offset, size_t size, const void* data);

    // DEVICE //
    void (*_destroy_impl)(struct mz_gpu_device* gpu);
} mz_gpu_device;

MZ_API mz_gpu_device mz_gpu_create_device(void);
MZ_API void mz_gpu_destroy_device(mz_gpu_device* gpu);

MZ_API uintptr_t mz_gpu_append_handle(mz_gpu_device* gpu, uintptr_t handle);

#endif // MUZZLE_GPU_DEVICE_H
