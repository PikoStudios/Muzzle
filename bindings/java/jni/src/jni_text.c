#include "../include/dev_pikostudios_muzzle_bridge_Text.h"
#include "../include/common.h"
#include "core/font.h"
#include "primitives/text.h"

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Text_draw(JNIEnv* env, jclass class, jobject applet, jstring text, jfloat x, jfloat y, jfloat size, jobject font, jobject tint)
{
    mz_applet* _applet = get_applet(env, applet);
    mz_tint _tint = get_tint(env, tint);

    jclass font_class = (*env)->GetObjectClass(env, font);
    jfieldID font_native_pointer_field = (*env)->GetFieldID(env, font_class, "nativePointer", "J");

    jlong font_pointer = (*env)->GetLongField(env, font, font_native_pointer_field);

    mz_font* _font = (mz_font*)(JLONG_TO_PTR(font_pointer));

    const char* _text = (*env)->GetStringUTFChars(env, text, NULL);

    mz_draw_text(_applet, _text, x, y, size, _font, _tint);

    (*env)->ReleaseStringUTFChars(env, text, _text);
}
