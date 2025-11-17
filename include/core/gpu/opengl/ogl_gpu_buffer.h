#ifndef MUZZLE_OPENGL_GPU_BUFFER_H
#define MUZZLE_OPENGL_GPU_BUFFER_H

#include "../../../backend.h"
#include "../gpu_device.h"
#include "../gpu_buffer.h"
#include <stdint.h>

MZ_API mz_gpu_buffer mz_gpu_ogl_create_buffer(mz_gpu_device* gpu, size_t size, mz_gpu_buffer_usage usage);
MZ_API void mz_gpu_ogl_destroy_buffer(mz_gpu_device* gpu, mz_gpu_buffer* buffer);
MZ_API void mz_gpu_ogl_allocate_buffer(mz_gpu_device* gpu, mz_gpu_buffer* buffer);
MZ_API void mz_gpu_ogl_write_buffer(mz_gpu_device* gpu, mz_gpu_buffer* buffer, size_t offset, size_t size, const void* data);
MZ_API void mz_gpu_ogl_lock_buffer(mz_gpu_device* gpu, mz_gpu_buffer* buffer);

#endif // MUZZLE_OPENGL_GPU_BUFFER_H
