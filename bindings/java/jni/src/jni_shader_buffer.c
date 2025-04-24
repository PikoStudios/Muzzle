#include "../include/dev_pikostudios_muzzle_bridge_ShaderBuffer.h"
#include "../include/common.h"
#include "core/shader.h"
#include "jni.h"

static mz_shader_buffer get_shader_buffer(JNIEnv* env, jobject object)
{
    jclass cls = (*env)->GetObjectClass(env, object);
    jfieldID id_field = (*env)->GetFieldID(env, cls, "id", "I");
    jfieldID index_field = (*env)->GetFieldID(env, cls, "index", "I");

    jint id = (*env)->GetIntField(env, object, id_field);
    jint index = (*env)->GetIntField(env, object, index_field);

    return (mz_shader_buffer){.id = id, .index = index};
}

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_ShaderBuffer_create(JNIEnv* env, jclass class, jint index, jobject bytebuffer, jlong size)
{
    void* data = (*env)->GetDirectBufferAddress(env, bytebuffer);
    size_t datasize = (size_t)(size);

    mz_shader_buffer buffer = mz_create_shader_buffer(index, data, datasize);

    jmethodID ctor = (*env)->GetMethodID(env, class, "<init>", "(II)V");
    jobject jbuffer = (*env)->NewObject(env, class, ctor, buffer.id, buffer.index);

    return jbuffer;
}

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_ShaderBuffer_createEmpty(JNIEnv* env, jclass class, jint index)
{
    mz_shader_buffer buffer = mz_create_shader_buffer(index, NULL, 0);

    jmethodID ctor = (*env)->GetMethodID(env, class, "<init>", "(II)V");
    jobject jbuffer = (*env)->NewObject(env, class, ctor, buffer.id, buffer.index);

    return jbuffer;
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_ShaderBuffer_unload(JNIEnv* env, jobject object)
{
    mz_shader_buffer buffer = get_shader_buffer(env, object);
    mz_unload_shader_buffer(buffer);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_ShaderBuffer_resize(JNIEnv* env, jobject object, jlong size)
{
    mz_shader_buffer buffer = get_shader_buffer(env, object);
    mz_realloc_shader_buffer(buffer, NULL, (size_t)(size));
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_ShaderBuffer_upload(JNIEnv* env, jobject object, jobject bytebuffer, jlong size, jlong offset)
{
    mz_shader_buffer buffer = get_shader_buffer(env, object);
    void* data = (*env)->GetDirectBufferAddress(env, bytebuffer);

    mz_upload_shader_buffer(buffer, offset, data, (size_t)(size));
}
