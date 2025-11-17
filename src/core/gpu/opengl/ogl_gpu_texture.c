#include "core/gpu/opengl/ogl_gpu_texture.h"
#include "core/gpu/gpu_device.h"
#include "core/gpu/gpu_texture.h"

#define TEXTURE_TYPE_AS_GL_ENUM_CASE(x) case GPU_TEXTURE_TYPE_##x: return GL_TEXTURE_##x
#define TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(x) case GPU_TEXTURE_INTERNAL_FORMAT_##x: return GL_##x
#define TEXTURE_FORMAT_AS_GL_ENUM_CASE(x) case GPU_TEXTURE_FORMAT_##x: return GL_##x
#define TEXTURE_DATA_TYPE_AS_GL_ENUM_CASE(x) case GPU_TEXTURE_DATA_TYPE_##x: return GL_##x


static inline GLenum texture_type_as_gl_enum(mz_gpu_texture_type type)
{
    switch (type)
    {
        TEXTURE_TYPE_AS_GL_ENUM_CASE(1D);
        TEXTURE_TYPE_AS_GL_ENUM_CASE(1D_ARRAY);
        TEXTURE_TYPE_AS_GL_ENUM_CASE(2D);
        TEXTURE_TYPE_AS_GL_ENUM_CASE(2D_ARRAY);
        TEXTURE_TYPE_AS_GL_ENUM_CASE(2D_MULTISAMPLE);
        TEXTURE_TYPE_AS_GL_ENUM_CASE(2D_MULTISAMPLE_ARRAY);
        TEXTURE_TYPE_AS_GL_ENUM_CASE(3D);
        TEXTURE_TYPE_AS_GL_ENUM_CASE(RECTANGLE);
        TEXTURE_TYPE_AS_GL_ENUM_CASE(CUBE_MAP);
        TEXTURE_TYPE_AS_GL_ENUM_CASE(CUBE_MAP_ARRAY);
        TEXTURE_TYPE_AS_GL_ENUM_CASE(BUFFER);
    }
}

static inline GLenum texture_internal_format_as_gl_enum(mz_gpu_texture_internal_format internal_format)
{
    switch (internal_format)
    {
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(R8);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(R8_SNORM);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(R16);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(R16_SNORM);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RG8);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RG8_SNORM);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RG16);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RG16_SNORM);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(R3_G3_B2);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB4);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB5);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB8);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB8_SNORM);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB10);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB12);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB16_SNORM);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGBA2);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGBA4);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB5_A1);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGBA8);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGBA8_SNORM);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB10_A2);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB10_A2UI);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGBA12);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGBA16);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(SRGB8);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(SRGB8_ALPHA8);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(R16F);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RG16F);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB16F);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGBA16F);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(R32F);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RG32F);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB32F);        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGBA32F);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(R11F_G11F_B10F);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB9_E5);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(R8I);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(R8UI);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(R16I);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(R16UI);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(R32I);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(R32UI);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RG8I);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RG8UI);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RG16I);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RG16UI);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RG32I);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RG32UI);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB8I);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB8UI);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB16I);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB16UI);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB32I);
        TEXTURE_INTERNAL_FORMAT_AS_GL_ENUM_CASE(RGB32UI);
    }
}

static inline GLenum texture_format_as_gl_enum(mz_gpu_texture_format format)
{
    switch (format)
    {
        case GPU_TEXTURE_FORMAT_R: return GL_RED;
        TEXTURE_FORMAT_AS_GL_ENUM_CASE(RG);
        TEXTURE_FORMAT_AS_GL_ENUM_CASE(RGB);
        TEXTURE_FORMAT_AS_GL_ENUM_CASE(BGR);
        TEXTURE_FORMAT_AS_GL_ENUM_CASE(RGBA);
        TEXTURE_FORMAT_AS_GL_ENUM_CASE(BGRA);
        TEXTURE_FORMAT_AS_GL_ENUM_CASE(DEPTH_COMPONENT);
        TEXTURE_FORMAT_AS_GL_ENUM_CASE(STENCIL_INDEX);
    }
}

static inline GLenum texture_data_type_as_gl_enum(mz_gpu_texture_data_type data_type)
{
    switch (data_type)
    {
        TEXTURE_DATA_TYPE_AS_GL_ENUM_CASE(UNSIGNED_BYTE);
        TEXTURE_DATA_TYPE_AS_GL_ENUM_CASE(BYTE);
        TEXTURE_DATA_TYPE_AS_GL_ENUM_CASE(UNSIGNED_SHORT);
        TEXTURE_DATA_TYPE_AS_GL_ENUM_CASE(SHORT);
        TEXTURE_DATA_TYPE_AS_GL_ENUM_CASE(UNSIGNED_INT);
        TEXTURE_DATA_TYPE_AS_GL_ENUM_CASE(INT);
        TEXTURE_DATA_TYPE_AS_GL_ENUM_CASE(FLOAT);
    }
}

uintptr_t mz_gpu_ogl_create_texture(mz_gpu_device* gpu, mz_gpu_texture_type type, uint32_t width, uint32_t height, uint32_t levels, mz_gpu_texture_internal_format internal_format)
{
    MZ_TRACK_FUNCTION();

    GLuint gpu_handle;
    glCreateTextures(texture_type_as_gl_enum(type), 1, &gpu_handle);

    glTextureStorage2D(gpu_handle, levels, texture_internal_format_as_gl_enum(internal_format), width, height);

    return mz_gpu_append_handle(gpu, gpu_handle);
}

void mz_gpu_ogl_destroy_texture(mz_gpu_device* gpu, uintptr_t handle)
{
    MZ_TRACK_FUNCTION();

    GLuint gpu_handle = (GLuint)(gpu->handles[handle]);
    glDeleteTextures(1, &gpu_handle);
}

void mz_gpu_ogl_write_texture(mz_gpu_device* gpu, uintptr_t handle, uint32_t level, uint32_t x, uint32_t y, uint32_t width, uint32_t height, mz_gpu_texture_format format, mz_gpu_texture_data_type data_type, const void* data)
{
    MZ_TRACK_FUNCTION();

    GLuint gpu_handle = (GLuint)(gpu->handles[handle]);
    glTextureSubImage2D(gpu_handle, level, x, y, width, height, texture_format_as_gl_enum(format), texture_data_type_as_gl_enum(data_type), data);
}

void mz_gpu_ogl_generate_mipmap(mz_gpu_device* gpu, uintptr_t handle)
{
    MZ_TRACK_FUNCTION();

    GLuint gpu_handle = (GLuint)(gpu->handles[handle]);
    glGenerateTextureMipmap(gpu_handle);
}
