#include "../include/dev_pikostudios_muzzle_bridge_GraphicsPipeline.h"
#include "../include/common.h"
#include "core/logging.h"
#include "core/memory.h"
#include "core/pipeline.h"
#include "jni.h"
#include <string.h>

#define GRAPHICS_PIPELINE_CTOR_METHOD_SIGNATURE "(JLdev/pikostudios/muzzle/bridge/Shader;)V"

static inline mz_graphics_pipeline* get_graphics_pipeline(JNIEnv* env, jobject obj)
{
    jclass class = (*env)->GetObjectClass(env, obj);
    jfieldID native_pointer_field = (*env)->GetFieldID(env, class, "nativePointer", "J");
    jlong native_pointer = (*env)->GetLongField(env, obj, native_pointer_field);

    return (mz_graphics_pipeline*)(JLONG_TO_PTR(native_pointer));
}

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_GraphicsPipeline_create(JNIEnv* env, jclass class, jobject shader, jintArray color_attachment_formats, jint framebuffer_width, jint framebuffer_height, jboolean create_depth_buffer, jint depth_buffer_type)
{
    mz_graphics_pipeline_descriptor pipeline_descriptor = (mz_graphics_pipeline_descriptor)
    {
        .color_attachment_count = (*env)->GetArrayLength(env, color_attachment_formats),
        .framebuffer_height = framebuffer_height,
        .framebuffer_width = framebuffer_width,
        .create_depth_buffer = create_depth_buffer
    };

    mz_shader _shader = get_shader(env, shader);
    pipeline_descriptor.shader = &_shader;

    jint formats[pipeline_descriptor.color_attachment_count];
    (*env)->GetIntArrayRegion(env, color_attachment_formats, 0, pipeline_descriptor.color_attachment_count, formats);

    for (int i = 0; i <pipeline_descriptor.color_attachment_count; i++)
    {
        switch (formats[i])
        {
            case 0: formats[i] = SPRITE_FORMAT_RGBA8; break;
            case 1: formats[i] = SPRITE_FORMAT_RGBA32F; break;
            default: __builtin_unreachable();
        }
    }

    pipeline_descriptor.color_attachment_formats = (mz_sprite_format*)(formats); // NOTE: this is very unsafe but jint should equal int and enum should equal int. better than copying again

    switch (depth_buffer_type)
    {
        case 0: break;
        case 1: pipeline_descriptor.depth_buffer_type = DEPTH_BUFFER_TYPE_RENDERBUFFER; break;
        case 2: pipeline_descriptor.depth_buffer_type = DEPTH_BUFFER_TYPE_TEXTURE; break;
        default:__builtin_unreachable();
    }

    mz_graphics_pipeline* pipeline = MZ_MALLOC(sizeof(mz_graphics_pipeline));

    if (pipeline == NULL)
    {
        mz_log_status(LOG_STATUS_FATAL_ERROR, "[JNI] Failed to allocate memory for mz_graphics_pipeline structure");
    }

    *pipeline = mz_create_graphics_pipeline(&pipeline_descriptor);

    jmethodID ctor = (*env)->GetMethodID(env, class, "<init>", GRAPHICS_PIPELINE_CTOR_METHOD_SIGNATURE);
    jobject jpipeline = (*env)->NewObject(env, class, ctor, PTR_TO_JLONG(pipeline), shader);

    return jpipeline;
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_GraphicsPipeline_clearDepthBuffer(JNIEnv* env, jobject obj, jfloat value)
{
    mz_graphics_pipeline* pipeline = get_graphics_pipeline(env, obj);
    mz_clear_graphics_pipeline_depth_buffer(pipeline, value);
}

JNIEXPORT jint JNICALL Java_dev_pikostudios_muzzle_bridge_GraphicsPipeline_getFramebufferID(JNIEnv* env, jobject obj)
{
    mz_graphics_pipeline* pipeline = get_graphics_pipeline(env, obj);
    return pipeline->fbo;
}


JNIEXPORT jint JNICALL Java_dev_pikostudios_muzzle_bridge_GraphicsPipeline_getFramebufferWidth(JNIEnv* env, jobject obj)
{
    mz_graphics_pipeline* pipeline = get_graphics_pipeline(env, obj);
    return pipeline->framebuffer_width;
}

JNIEXPORT jint JNICALL Java_dev_pikostudios_muzzle_bridge_GraphicsPipeline_getFramebufferHeight(JNIEnv* env, jobject obj)
{
    mz_graphics_pipeline* pipeline = get_graphics_pipeline(env, obj);
    return pipeline->framebuffer_height;
}

JNIEXPORT jint JNICALL Java_dev_pikostudios_muzzle_bridge_GraphicsPipeline_getColorAttachmentsCount(JNIEnv* env, jobject obj)
{
    mz_graphics_pipeline* pipeline = get_graphics_pipeline(env, obj);
    return pipeline->color_attachments_len;
}

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_GraphicsPipeline_getColorAttachmentTexture(JNIEnv* env, jobject obj, jint index)
{
    static jclass sprite_class = NULL;

    mz_graphics_pipeline* pipeline = get_graphics_pipeline(env, obj);

    mz_sprite sprite = mz_get_graphics_pipeline_color_attachment_texture(pipeline, index);

    if (sprite_class == NULL)
    {
        jclass sprite_class_local = (*env)->FindClass(env, "dev/pikostudios/muzzle/bridge/Sprite");
        sprite_class = (*env)->NewGlobalRef(env, sprite_class_local);
        (*env)->DeleteLocalRef(env, sprite_class_local);
    }

    jmethodID sprite_ctor = (*env)->GetMethodID(env, sprite_class, "<init>", "(III)V");
    jobject jsprite = (*env)->NewObject(env, sprite_class, sprite_ctor, sprite.width, sprite.height, sprite._id);

    return jsprite;
}

JNIEXPORT jint JNICALL Java_dev_pikostudios_muzzle_bridge_GraphicsPipeline_getColorAttachmentID(JNIEnv* env, jobject obj, jint index)
{
    mz_graphics_pipeline* pipeline = get_graphics_pipeline(env, obj);
    return pipeline->color_attachment_handles[index];
}

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_GraphicsPipeline_getDepthBufferTexture(JNIEnv* env, jobject obj)
{
    static jclass sprite_class = NULL;

    mz_graphics_pipeline* pipeline = get_graphics_pipeline(env, obj);

    mz_sprite sprite = mz_get_graphics_pipeline_depth_buffer_texture(pipeline);

    if (sprite_class == NULL)
    {
        jclass sprite_class_local = (*env)->FindClass(env, "dev/pikostudios/muzzle/bridge/Sprite");
        sprite_class = (*env)->NewGlobalRef(env, sprite_class_local);
        (*env)->DeleteLocalRef(env, sprite_class_local);
    }

    jmethodID sprite_ctor = (*env)->GetMethodID(env, sprite_class, "<init>", "(III)V");
    jobject jsprite = (*env)->NewObject(env, sprite_class, sprite_ctor, sprite.width, sprite.height, sprite._id);

    return jsprite;
}

JNIEXPORT jint JNICALL Java_dev_pikostudios_muzzle_bridge_GraphicsPipeline_getDepthBufferID(JNIEnv* env, jobject obj)
{
    mz_graphics_pipeline* pipeline = get_graphics_pipeline(env, obj);
    return pipeline->depth_buffer;
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_GraphicsPipeline_unload(JNIEnv* env, jobject obj)
{
    jclass class = (*env)->GetObjectClass(env, obj);
    jfieldID native_pointer_id = (*env)->GetFieldID(env, class, "nativePointer", "J");
    jlong native_pointer = (*env)->GetLongField(env, obj, native_pointer_id);

    mz_graphics_pipeline* pipeline = (mz_graphics_pipeline*)(JLONG_TO_PTR(native_pointer));

    mz_unload_graphics_pipeline(pipeline);

    MZ_FREE(pipeline);

    (*env)->SetLongField(env, obj, native_pointer_id, 0L);
}

JNIEXPORT jint JNICALL Java_dev_pikostudios_muzzle_bridge_GraphicsPipeline__1getDepthBufferType(JNIEnv* env, jobject obj)
{
    mz_graphics_pipeline* pipeline = get_graphics_pipeline(env, obj);
    return pipeline->depth_buffer_type;
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_GraphicsPipeline__1clearColorAttachments(JNIEnv* env, jobject obj, jint r, jint g, jint b, jint a)
{
    mz_graphics_pipeline* pipeline = get_graphics_pipeline(env, obj);
    mz_clear_graphics_pipeline_color_attachments(pipeline, (mz_tint){r,g,b,a});
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_GraphicsPipeline__1dispatch(JNIEnv* env, jobject obj, jobject vertex_buffer, jlong start, jlong count)
{
    mz_graphics_pipeline* pipeline = get_graphics_pipeline(env, obj);
    mz_vertex_buffer* buffer = get_vertex_buffer(env, obj);

    mz_dispatch_graphics_pipeline(pipeline, buffer, start, count);
}
