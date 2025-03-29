#include "../include/dev_pikostudios_muzzle_bridge_Shader.h"
#include "../include/common.h"
#include "core/shader.h"
#include "jni.h"

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_Shader_create(JNIEnv* env, jclass class, jstring vertex_source, jstring fragment_source, jint type)
{
    const char* vertex_src = (*env)->GetStringUTFChars(env, vertex_source, NULL);
    const char* fragment_src = (*env)->GetStringUTFChars(env, fragment_source, NULL);

    mz_shader shader = mz_create_shader(vertex_src, fragment_src, type);

    jmethodID ctor = (*env)->GetMethodID(env, class, "<init>", "(II)V");
    jobject jshader = (*env)->NewObject(env, class, ctor, shader.pid, shader.type);


    (*env)->ReleaseStringUTFChars(env, vertex_source, vertex_src);
    (*env)->ReleaseStringUTFChars(env, fragment_source, fragment_src);

    return jshader;
}

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_Shader_load(JNIEnv* env, jclass class, jstring vertex_filepath, jstring fragment_filepath, jint type)
{
    const char* vertex_fp = (*env)->GetStringUTFChars(env, vertex_filepath, NULL);
    const char* fragment_fp = (*env)->GetStringUTFChars(env, fragment_filepath, NULL);

    mz_shader shader = mz_load_shader(vertex_fp, fragment_fp, type);

    jmethodID ctor = (*env)->GetMethodID(env, class, "<init>", "(II)V");
    jobject jshader = (*env)->NewObject(env, class, ctor, shader.pid, shader.type);

    (*env)->ReleaseStringUTFChars(env, vertex_filepath, vertex_fp);
    (*env)->ReleaseStringUTFChars(env, fragment_filepath, fragment_fp);

    return jshader;
}
