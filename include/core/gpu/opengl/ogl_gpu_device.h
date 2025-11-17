#ifndef MUZZLE_OPENGL_GPU_DEVICE_H
#define MUZZLE_OPENGL_GPU_DEVICE_H

#include "../../../backend.h"
#include "../gpu_device.h"
#include <stdint.h>

typedef enum : uint16_t
{
    GPU_HANDLE_TYPE_BUFFER = 0,
    GPU_HANDLE_TYPE_TEXTURE = 1
} mz_ogl_gpu_handle_type;

typedef struct mz_ogl_gpu_device_data
{

} mz_ogl_gpu_device_data;

MZ_API void mz_gpu_ogl_init_device(mz_gpu_device* gpu);
MZ_API void mz_gpu_ogl_destroy_device(mz_gpu_device* gpu);
MZ_API void mz_gpu_ogl_append_handle_type(mz_gpu_device* gpu);

#endif // MUZZLE_OPENGL_GPU_DEVICE_H
