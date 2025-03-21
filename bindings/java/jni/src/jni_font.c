#include "../include/dev_pikostudios_muzzle_bridge_Font.h"
#include "core/font.h"
#include "../include/common.h"
#include "core/logging.h"
#include "jni.h"

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_Font_load(JNIEnv* env, jclass class, jobject applet, jstring filepath)
{
    mz_applet* _applet = get_applet(env, applet);

    const char* fontpath = (*env)->GetStringUTFChars(env, filepath, NULL);

    mz_font* font = MZ_MALLOC(sizeof(mz_font));

    if (font == NULL)
    {
        mz_log_status(LOG_STATUS_FATAL_ERROR, "[JNI] :: Could not initialize memory for font object");
    }

    *font = mz_load_font(_applet, fontpath);

    (*env)->ReleaseStringUTFChars(env, filepath, fontpath);

    jmethodID ctor = (*env)->GetMethodID(env, class, "<init>", "(J)V");
    jobject jfont = (*env)->NewObject(env, class, ctor, PTR_TO_JLONG(font));

    return jfont;
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Font_unload(JNIEnv* env, jclass class, jobject font)
{
    jfieldID native_pointer_field = (*env)->GetFieldID(env, class, "nativePointer", "J");

    jlong native_pointer = (*env)->GetLongField(env, font, native_pointer_field);

    mz_font* _font = (mz_font*)(JLONG_TO_PTR(native_pointer));

    mz_unload_font(_font);
    MZ_FREE(_font);

    (*env)->SetLongField(env, font, native_pointer_field, 0L);
}
