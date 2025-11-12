#ifndef MUZZLE_GPU_DEVICE_H
#define MUZZLE_GPU_DEVICE_H

#ifndef MUZZLE_GPU_DEVICE_HANDLES_INITIAL_CAPACITY
    #define MUZZLE_GPU_DEVICE_HANDLES_INITIAL_CAPACITY 256
#endif

#include "../../backend.h"
#include <stdint.h>

typedef enum
{
    GPU_BUFFER_USAGE_STATIC = 0,
    GPU_BUFFER_USAGE_DYNAMIC = 1,
    GPU_BUFFER_USAGE_STREAM = 2,
} mz_gpu_buffer_usage;

typedef struct mz_gpu_device
{
    void* impl_data;

    uintptr_t* handles;
    size_t handles_size;
    size_t handles_capacity;

    uintptr_t (*create_buffer)(struct mz_gpu_device* gpu, size_t size, mz_gpu_buffer_usage usage);
    void (*destroy_buffer)(struct mz_gpu_device* gpu, uintptr_t handle);

    void (*_destroy_impl)(struct mz_gpu_device* gpu);
} mz_gpu_device;

MZ_API mz_gpu_device mz_gpu_create_device(void);
MZ_API void mz_gpu_destroy_device(mz_gpu_device* gpu);
MZ_API void mz_gpu_append_handle(mz_gpu_device* gpu, uintptr_t handle);

#endif // MUZZLE_GPU_DEVICE_H
