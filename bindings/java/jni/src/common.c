#include "../include/common.h"
#include "core/tint.h"
#include "jni.h"

mz_applet* get_applet_with_cls(JNIEnv* env, jclass class, jobject obj)
{
    jfieldID native_pointer_field = (*env)->GetFieldID(env, class, "nativePointer", "J");
    jlong native_pointer = (*env)->GetLongField(env, obj, native_pointer_field);

    return (mz_applet*)(JLONG_TO_PTR(native_pointer));
}

mz_applet* get_applet(JNIEnv* env, jobject obj)
{
    jclass class = (*env)->GetObjectClass(env, obj);
    return get_applet_with_cls(env, class, obj);
}

mz_shader get_shader_with_cls(JNIEnv* env, jclass class, jobject obj)
{
    jfieldID id_field = (*env)->GetFieldID(env, class, "id", "I");
    jint id = (*env)->GetIntField(env, obj, id_field);

    return (mz_shader){.pid=id};
}

mz_shader get_shader(JNIEnv* env, jobject obj)
{
    jclass class = (*env)->GetObjectClass(env, obj);
    return get_shader_with_cls(env, class, obj);
}

mz_shader_pass get_shader_pass_with_cls(JNIEnv* env, jclass class, jobject obj)
{
    jfieldID shader_id_field = (*env)->GetFieldID(env, class, "shaderIDCache", "I");
    jfieldID depth_loc_field = (*env)->GetFieldID(env, class, "depthTextureUniformLocation", "I");
    jfieldID scr_texture_loc_field = (*env)->GetFieldID(env, class, "screenTextureUniformLocation", "I");
    jfieldID res_loc_field = (*env)->GetFieldID(env, class, "resolutionUniformLocation", "I");

    jint shader_id = (*env)->GetIntField(env, obj, shader_id_field);
    jint depth_loc = (*env)->GetIntField(env, obj, depth_loc_field);
    jint scr_texture_loc = (*env)->GetIntField(env, obj, scr_texture_loc_field);
    jint res_loc = (*env)->GetIntField(env, obj, res_loc_field);

    return (mz_shader_pass)
    {
        .shader = (mz_shader){.pid = shader_id},
        .depth_texture_uniform_loc = depth_loc,
        .screen_texture_uniform_loc = scr_texture_loc,
        .resolution_uniform_loc = res_loc
    };
}

mz_shader_pass get_shader_pass(JNIEnv* env, jobject obj)
{
    jclass class = (*env)->GetObjectClass(env, obj);
    return get_shader_pass_with_cls(env, class, obj);
}

mz_tint get_tint_with_cls(JNIEnv* env, jclass class, jobject obj)
{
    jfieldID r_field = (*env)->GetFieldID(env, class, "r", "I");
    jfieldID g_field = (*env)->GetFieldID(env, class, "g", "I");
    jfieldID b_field = (*env)->GetFieldID(env, class, "b", "I");
    jfieldID a_field = (*env)->GetFieldID(env, class, "a", "I");

    jint red = (*env)->GetIntField(env, obj, r_field);
    jint green = (*env)->GetIntField(env, obj, g_field);
    jint blue = (*env)->GetIntField(env, obj, b_field);
    jint alpha = (*env)->GetIntField(env, obj, a_field);

    return (mz_tint){red, green, blue, alpha};
}

mz_tint get_tint(JNIEnv* env, jobject obj)
{
    jclass class = (*env)->GetObjectClass(env, obj);
    return get_tint_with_cls(env, class, obj);
}
