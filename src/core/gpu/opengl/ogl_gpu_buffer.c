#include "core/gpu/opengl/ogl_gpu_buffer.h"
#include "backend.h"
#include "core/gpu/gpu_buffer.h"
#include "core/gpu/gpu_device.h"

mz_gpu_buffer mz_gpu_ogl_create_buffer(mz_gpu_device* gpu, size_t size, mz_gpu_buffer_usage usage)
{
    MZ_TRACK_FUNCTION();

    GLuint gpu_handle;
    glCreateBuffers(1, &gpu_handle);

    uintptr_t handle = mz_gpu_append_handle(gpu, gpu_handle);

    return (mz_gpu_buffer)
    {
        .handle = handle,
        .size = size,
        .usage = usage
    };
}

void mz_gpu_ogl_destroy_buffer(mz_gpu_device* gpu, mz_gpu_buffer* buffer)
{
    MZ_TRACK_FUNCTION();

    GLuint gpu_handle = (GLuint)(gpu->handles[buffer->handle]);
    glDeleteBuffers(1, &gpu_handle);
    buffer->size = 0;
}

static inline GLenum buffer_usage_as_gl_enum(mz_gpu_buffer_usage usage)
{
    switch (usage)
    {
    case GPU_BUFFER_USAGE_STATIC:
        return GL_STATIC_DRAW;

    case GPU_BUFFER_USAGE_STREAM:
        return GL_STREAM_DRAW;

    case GPU_BUFFER_USAGE_DYNAMIC:
        return GL_DYNAMIC_DRAW;
    }
}

void mz_gpu_ogl_allocate_buffer(mz_gpu_device* gpu, mz_gpu_buffer* buffer)
{
    MZ_TRACK_FUNCTION();

    GLuint gpu_handle = (GLuint)(gpu->handles[buffer->handle]);
    GLenum usage = buffer_usage_as_gl_enum(buffer->usage);
    
    glNamedBufferData(gpu_handle, buffer->size, NULL, usage);
}

void mz_gpu_ogl_write_buffer(mz_gpu_device* gpu, mz_gpu_buffer* buffer, size_t offset, size_t size, const void* data)
{
    MZ_TRACK_FUNCTION();

    GLuint gpu_handle = (GLuint)(gpu->handles[buffer->handle]);
    glNamedBufferSubData(gpu_handle, offset, size, data);
}

void mz_gpu_ogl_lock_buffer(mz_gpu_device* gpu, mz_gpu_buffer* buffer)
{
    // Empty implementation
}
