#include "../include/dev_pikostudios_muzzle_bridge_Shader.h"
#include "../include/common.h"
#include "core/shader.h"
#include "jni.h"

static mz_shader get_shader(JNIEnv* env, jobject shader)
{
    jclass class = (*env)->GetObjectClass(env, shader);

    jfieldID id_field = (*env)->GetFieldID(env, class, "id", "I");
    jfieldID type_field = (*env)->GetFieldID(env, class, "type", "I");

    jint id = (*env)->GetIntField(env, shader, id_field);
    jint type = (*env)->GetIntField(env, shader, type_field);

    return (mz_shader){.pid=id, .type=type};
}

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

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Shader_unload(JNIEnv* env, jobject object)
{
    jclass class = (*env)->GetObjectClass(env, object);

    jfieldID id_field = (*env)->GetFieldID(env, class, "id", "I");
    jint id = (*env)->GetIntField(env, object, id_field);

    mz_unload_shader((mz_shader){.pid=id});
    (*env)->SetIntField(env, object, id_field, 0);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Shader__1use(JNIEnv* env, jobject object, jobject applet)
{
    mz_applet* _applet = get_applet(env, applet);
    mz_shader shader = get_shader(env, object);
    mz_use_shader_pass(_applet, shader);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Shader__1beginShader(JNIEnv* env, jobject object, jobject applet)
{
    mz_applet* _applet = get_applet(env, applet);
    mz_shader shader = get_shader(env, object);
    mz_begin_shader(_applet, shader);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Shader__1endShader(JNIEnv* env, jobject object, jobject applet)
{
    mz_applet* _applet = get_applet(env, applet);
    mz_shader shader = get_shader(env, object);
    mz_end_shader(_applet, shader);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Shader_uploadUniform__Ljava_lang_String_2I(JNIEnv* env, jobject object, jstring uniform, jint value)
{
    mz_shader shader = get_shader(env, object);
    const char* uniform_name = (*env)->GetStringUTFChars(env, uniform, NULL);

    mz_upload_uniform_int(shader, uniform_name, value);

    (*env)->ReleaseStringUTFChars(env, uniform, uniform_name);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Shader_uploadUniform__Ljava_lang_String_2F(JNIEnv* env, jobject object, jstring uniform, jfloat value)
{
    mz_shader shader = get_shader(env, object);
    const char* uniform_name = (*env)->GetStringUTFChars(env, uniform, NULL);

    mz_upload_uniform_float(shader, uniform_name, value);

    (*env)->ReleaseStringUTFChars(env, uniform, uniform_name);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Shader_uploadUniform__Ljava_lang_String_2FF(JNIEnv* env, jobject object, jstring uniform, jfloat x, jfloat y)
{
    mz_shader shader = get_shader(env, object);
    const char* uniform_name = (*env)->GetStringUTFChars(env, uniform, NULL);

    mz_upload_uniform_vec2(shader, uniform_name, (mz_vec2){x,y});

    (*env)->ReleaseStringUTFChars(env, uniform, uniform_name);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Shader_uploadUniform__Ljava_lang_String_2FFF(JNIEnv* env, jobject object, jstring uniform, jfloat x, jfloat y, jfloat z)
{
    mz_shader shader = get_shader(env, object);
    const char* uniform_name = (*env)->GetStringUTFChars(env, uniform, NULL);

    mz_upload_uniform_vec3(shader, uniform_name, (mz_vec3){x,y,z});

    (*env)->ReleaseStringUTFChars(env, uniform, uniform_name);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Shader_uploadUniform__Ljava_lang_String_2FFFF(JNIEnv* env, jobject object, jstring uniform, jfloat x, jfloat y, jfloat z, jfloat w)
{
    mz_shader shader = get_shader(env, object);
    const char* uniform_name = (*env)->GetStringUTFChars(env, uniform, NULL);

    mz_upload_uniform_vec4(shader, uniform_name, (mz_vec4){x,y,z,w});

    (*env)->ReleaseStringUTFChars(env, uniform, uniform_name);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Shader_uploadUniformMat3(JNIEnv* env, jobject object, jstring uniform, jfloatArray matrix)
{
    mz_shader shader = get_shader(env, object);
    jfloat* elems = (*env)->GetFloatArrayElements(env, matrix, NULL);
    const char* uniform_name = (*env)->GetStringUTFChars(env, uniform, NULL);

    mz_upload_uniform_mat3(shader, uniform_name, elems);

    (*env)->ReleaseFloatArrayElements(env, matrix, elems, JNI_ABORT);
    (*env)->ReleaseStringUTFChars(env, uniform, uniform_name);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Shader_uploadUniformMat4(JNIEnv* env, jobject object, jstring uniform, jfloatArray matrix)
{
    mz_shader shader = get_shader(env, object);
    jfloat* elems = (*env)->GetFloatArrayElements(env, matrix, NULL);
    const char* uniform_name = (*env)->GetStringUTFChars(env, uniform, NULL);

    mz_upload_uniform_mat4(shader, uniform_name, elems);

    (*env)->ReleaseFloatArrayElements(env, matrix, elems, JNI_ABORT);
    (*env)->ReleaseStringUTFChars(env, uniform, uniform_name);
}
