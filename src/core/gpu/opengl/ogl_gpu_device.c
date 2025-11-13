#include "core/gpu/opengl/ogl_gpu_device.h"
#include "core/gpu/gpu_device.h"
#include "core/gpu/opengl/ogl_gpu_buffer.h"
#include <stdint.h>

void mz_gpu_ogl_init_device(mz_gpu_device* gpu)
{
    gpu->create_buffer = mz_gpu_ogl_create_buffer;
    gpu->destroy_buffer = mz_gpu_ogl_destroy_buffer;
    gpu->allocate_buffer = mz_gpu_ogl_allocate_buffer;
    
    gpu->_destroy_impl = mz_gpu_ogl_destroy_device;
}

void mz_gpu_ogl_destroy_device(mz_gpu_device* gpu)
{
    gpu->impl_data = NULL;
}
