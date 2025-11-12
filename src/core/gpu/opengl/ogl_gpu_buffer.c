#include "core/gpu/opengl/ogl_gpu_buffer.h"
#include "core/gpu/gpu_device.h"

uintptr_t mz_gpu_ogl_create_buffer(mz_gpu_device* gpu, size_t size, mz_gpu_buffer_usage usage)
{
    GLuint handle;
    glCreateBuffers(1, &handle);

    mz_gpu_append_handle(gpu, handle);
}

void mz_gpu_ogl_destroy_buffer(mz_gpu_device* gpu, uintptr_t handle)
{

}
