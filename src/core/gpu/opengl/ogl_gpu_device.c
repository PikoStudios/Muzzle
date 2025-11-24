#include "core/gpu/opengl/ogl_gpu_device.h"
#include "core/gpu/gpu_device.h"
#include "core/gpu/opengl/ogl_gpu_buffer.h"
#include "core/gpu/opengl/ogl_gpu_texture.h"

void mz_gpu_ogl_init_device(mz_gpu_device* gpu)
{
    MZ_TRACK_FUNCTION();

    gpu->impl_data = NULL;

    gpu->create_buffer = mz_gpu_ogl_create_buffer;
    gpu->destroy_buffer = mz_gpu_ogl_destroy_buffer;
    gpu->allocate_buffer = mz_gpu_ogl_allocate_buffer;
    gpu->write_buffer = mz_gpu_ogl_write_buffer;

    gpu->create_texture = mz_gpu_ogl_create_texture;
    gpu->destroy_texture = mz_gpu_ogl_destroy_texture;
    gpu->write_texture = mz_gpu_ogl_write_texture;
    gpu->generate_mipmap = mz_gpu_ogl_generate_mipmap;

    gpu->_destroy_impl = mz_gpu_ogl_destroy_device;
}

void mz_gpu_ogl_destroy_device(mz_gpu_device* gpu)
{
    MZ_TRACK_FUNCTION();
    gpu->impl_data = NULL;
}
