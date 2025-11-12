#ifndef MUZZLE_OPENGL_GPU_BUFFER_H
#define MUZZLE_OPENGL_GPU_BUFFER_H

#include "../../../backend.h"
#include "../gpu_device.h"
#include <stdint.h>

MZ_API uintptr_t mz_gpu_ogl_create_buffer(mz_gpu_device* gpu, size_t size, mz_gpu_buffer_usage usage);
MZ_API void mz_gpu_ogl_destroy_buffer(mz_gpu_device* gpu, uintptr_t handle);

#endif // MUZZLE_OPENGL_GPU_BUFFER_H
