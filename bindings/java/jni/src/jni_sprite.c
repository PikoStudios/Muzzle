#include "../include/dev_pikostudios_muzzle_bridge_Sprite.h"
#include "core/logging.h"
#include "core/memory.h"
#include "jni.h"
#include "primitives/sprite.h"
#include "../include/common.h"

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_Sprite_load(JNIEnv* env, jclass class, jstring filepath)
{
    const char* spritepath = (*env)->GetStringUTFChars(env, filepath, NULL);

    mz_sprite sprite = mz_load_sprite(spritepath);
    (*env)->ReleaseStringUTFChars(env, filepath, spritepath);

    jmethodID ctor = (*env)->GetMethodID(env, class, "<init>", "(III)V");
    jobject jsprite = (*env)->NewObject(env, class, ctor, sprite.width, sprite.height, sprite._id);

    return jsprite;
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Sprite_unload(JNIEnv* env, jclass class, jobject sprite)
{
    jfieldID id_field = (*env)->GetFieldID(env, class, "id", "I");
    jint id = (*env)->GetIntField(env, sprite, id_field);

    mz_sprite _sprite = (mz_sprite){._id = id};
    mz_unload_sprite(&_sprite);

    (*env)->SetIntField(env, sprite, id_field, -1);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Sprite_draw(JNIEnv* env, jobject object, jobject applet, jfloat x, jfloat y, jobject tint)
{
    // TODO;
}
