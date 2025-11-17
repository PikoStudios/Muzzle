#ifndef MUZZLE_OPENGL_GPU_TEXTURE_H
#define MUZZLE_OPENGL_GPU_TEXTURE_H

#include "../gpu_device.h"
#include "../../../backend.h"
#include <stdint.h>

MZ_API uintptr_t mz_gpu_ogl_create_texture(mz_gpu_device* gpu, mz_gpu_texture_type type, uint32_t width, uint32_t height, uint32_t levels, mz_gpu_texture_internal_format internal_format);
MZ_API void mz_gpu_ogl_destroy_texture(mz_gpu_device* gpu, uintptr_t handle);

MZ_API void mz_gpu_ogl_write_texture(mz_gpu_device* gpu, uintptr_t handle, uint32_t level, uint32_t x, uint32_t y, uint32_t width, uint32_t height, mz_gpu_texture_format format, mz_gpu_texture_data_type data_type, const void* data);

MZ_API void mz_gpu_ogl_generate_mipmap(mz_gpu_device* gpu, uintptr_t handle);

#endif // MUZZLE_GPU_TEXTURE_H
