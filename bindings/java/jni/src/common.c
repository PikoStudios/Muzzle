#include "../include/common.h"
#include "core/tint.h"
#include "jni.h"

mz_applet* get_applet(JNIEnv* env, jobject obj)
{
    jclass class = (*env)->GetObjectClass(env, obj);
    jfieldID native_pointer_field = (*env)->GetFieldID(env, class, "nativePointer", "J");
    jlong native_pointer = (*env)->GetLongField(env, obj, native_pointer_field);

    return (mz_applet*)(JLONG_TO_PTR(native_pointer));
}

mz_tint get_tint(JNIEnv* env, jobject obj)
{
    jclass class = (*env)->GetObjectClass(env, obj);
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
