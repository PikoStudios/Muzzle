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
#include "gpu_texture.h"
#include <stdint.h>

typedef struct mz_gpu_device
{
    void* impl_data;

    uintptr_t* handles;
    size_t handles_size;
    size_t handles_capacity;

    // BUFFERS //

    // Creates a buffer with size and usage hints
    mz_gpu_buffer (*create_buffer)(struct mz_gpu_device* gpu, size_t size, mz_gpu_buffer_usage usage);

    // Destroys the buffer
    void (*destroy_buffer)(struct mz_gpu_device* gpu, mz_gpu_buffer* buffer);

    // Allocates memory to a buffer
    void (*allocate_buffer)(struct mz_gpu_device* gpu, mz_gpu_buffer* buffer);

    // Writes to a specified portion of a buffer. Buffer must first be allocated
    void (*write_buffer)(struct mz_gpu_device* gpu, mz_gpu_buffer* buffer, size_t offset, size_t size, const void* data);

    // Lock the buffer (prevents any subsequent CPU writes to the buffer)
    void (*lock_buffer)(struct mz_gpu_device* gpu, mz_gpu_buffer* buffer);

    // TEXTURES //

    // Creates a texture on the GPU
    uintptr_t (*create_texture)(struct mz_gpu_device* gpu, mz_gpu_texture_type type, uint32_t width, uint32_t height, uint32_t levels, mz_gpu_texture_internal_format internal_format);

    // Destroys the texture
    void (*destroy_texture)(struct mz_gpu_device* gpu, uintptr_t handle);

    // Writes to a specified portion of a texture
    void (*write_texture)(struct mz_gpu_device* gpu, uintptr_t handle, uint32_t level, uint32_t x, uint32_t y, uint32_t width, uint32_t height, mz_gpu_texture_format format, mz_gpu_texture_data_type data_type, const void* data);

    // Generates mipmap of a texture
    void (*generate_mipmap)(struct mz_gpu_device* gpu, uintptr_t handle);

    // TODO: Methods to configure sampler

    // DEVICE //

    // Destroy implementation related resources
    void (*_destroy_impl)(struct mz_gpu_device* gpu);
} mz_gpu_device;

MZ_API mz_gpu_device mz_gpu_create_device(void);
MZ_API void mz_gpu_destroy_device(mz_gpu_device* gpu);

MZ_API uintptr_t mz_gpu_append_handle(mz_gpu_device* gpu, uintptr_t handle);

#endif // MUZZLE_GPU_DEVICE_H
