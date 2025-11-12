#ifndef MUZZLE_OPENGL_GPU_DEVICE_H
#define MUZZLE_OPENGL_GPU_DEVICE_H

#include "../../../backend.h"
#include "../gpu_device.h"

MZ_API void mz_gpu_ogl_init_device(mz_gpu_device* gpu);
MZ_API void mz_gpu_ogl_destroy_device(mz_gpu_device* gpu);

#endif // MUZZLE_OPENGL_GPU_DEVICE_H
