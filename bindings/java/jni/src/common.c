#include "../include/common.h"

mz_applet* get_applet(JNIEnv* env, jobject obj)
{
    jclass class = (*env)->GetObjectClass(env, obj);
    jfieldID native_pointer_field = (*env)->GetFieldID(env, class, "nativePointer", "J");
    jlong native_pointer = (*env)->GetLongField(env, obj, native_pointer_field);

    return (mz_applet*)(JLONG_TO_PTR(native_pointer));
}
