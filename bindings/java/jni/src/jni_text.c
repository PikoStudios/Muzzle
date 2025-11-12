#include "../include/dev_pikostudios_muzzle_bridge_Text.h"
#include "../include/common.h"
#include "core/font.h"
#include "primitives/text.h"

JNIEXPORT jfloat JNICALL Java_dev_pikostudios_muzzle_bridge_Text_measureWidth(JNIEnv* env, jclass class, jstring text, jfloat font_size, jobject font)
{
    UNUSED(class);
    
    if (font == NULL)
    {
        jclass nullptrexcpt = (*env)->FindClass(env, "java/lang/NullPointerException");
        (*env)->ThrowNew(env, nullptrexcpt, "font is null");
        return 0;
    }

    jclass font_class = (*env)->GetObjectClass(env, font);
    jfieldID font_native_pointer_field = (*env)->GetFieldID(env, font_class, "nativePointer", "J");

    jlong font_pointer = (*env)->GetLongField(env, font, font_native_pointer_field);

    mz_font* _font = (mz_font*)(JLONG_TO_PTR(font_pointer));

    const char* _text = (*env)->GetStringUTFChars(env, text, NULL);

    mz_vec2 dimensions = mz_measure_text(_text, font_size, _font);

    (*env)->ReleaseStringUTFChars(env, text, _text);

    return dimensions.x;
}

JNIEXPORT jfloat JNICALL Java_dev_pikostudios_muzzle_bridge_Text_measureHeight(JNIEnv* env, jclass class, jstring text, jfloat font_size, jobject font)
{
    UNUSED(class);
    
    if (font == NULL)
    {
        jclass nullptrexcpt = (*env)->FindClass(env, "java/lang/NullPointerException");
        (*env)->ThrowNew(env, nullptrexcpt, "font is null");
        return 0;
    }

    jclass font_class = (*env)->GetObjectClass(env, font);
    jfieldID font_native_pointer_field = (*env)->GetFieldID(env, font_class, "nativePointer", "J");

    jlong font_pointer = (*env)->GetLongField(env, font, font_native_pointer_field);

    mz_font* _font = (mz_font*)(JLONG_TO_PTR(font_pointer));

    const char* _text = (*env)->GetStringUTFChars(env, text, NULL);

    mz_vec2 dimensions = mz_measure_text(_text, font_size, _font);

    (*env)->ReleaseStringUTFChars(env, text, _text);

    return dimensions.y;
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Text_draw(JNIEnv* env, jclass class, jobject applet, jstring text, jfloat x, jfloat y, jfloat size, jobject font, jobject tint)
{
    UNUSED(class);
    
    mz_applet* _applet = get_applet(env, applet);
    mz_tint _tint = get_tint(env, tint);

    if (font == NULL)
    {
        jclass nullptrexcpt = (*env)->FindClass(env, "java/lang/NullPointerException");
        (*env)->ThrowNew(env, nullptrexcpt, "font is null");
        return;
    }

    jclass font_class = (*env)->GetObjectClass(env, font);
    jfieldID font_native_pointer_field = (*env)->GetFieldID(env, font_class, "nativePointer", "J");

    jlong font_pointer = (*env)->GetLongField(env, font, font_native_pointer_field);

    mz_font* _font = (mz_font*)(JLONG_TO_PTR(font_pointer));

    const char* _text = (*env)->GetStringUTFChars(env, text, NULL);

    mz_draw_text(_applet, _text, x, y, size, _font, _tint);

    (*env)->ReleaseStringUTFChars(env, text, _text);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Text_drawCentered(JNIEnv* env, jclass class, jobject applet, jstring text, jfloat x, jfloat y, jfloat size, jobject font, jobject tint)
{
    UNUSED(class);
    
    mz_applet* _applet = get_applet(env, applet);
    mz_tint _tint = get_tint(env, tint);

    if (font == NULL)
    {
        jclass nullptrexcpt = (*env)->FindClass(env, "java/lang/NullPointerException");
        (*env)->ThrowNew(env, nullptrexcpt, "font is null");
        return;
    }

    jclass font_class = (*env)->GetObjectClass(env, font);
    jfieldID font_native_pointer_field = (*env)->GetFieldID(env, font_class, "nativePointer", "J");

    jlong font_pointer = (*env)->GetLongField(env, font, font_native_pointer_field);

    mz_font* _font = (mz_font*)(JLONG_TO_PTR(font_pointer));

    const char* _text = (*env)->GetStringUTFChars(env, text, NULL);

    mz_draw_text_centered(_applet, _text, x, y, size, _font, _tint);

    (*env)->ReleaseStringUTFChars(env, text, _text);
}
