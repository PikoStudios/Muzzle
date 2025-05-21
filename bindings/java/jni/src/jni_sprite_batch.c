#include "../include/dev_pikostudios_muzzle_bridge_SpriteBatch.h"
#include "../include/common.h"
#include "core/applet.h"
#include "core/logging.h"
#include "jni.h"
#include "jni_md.h"
#include "primitives/sprite.h"

static mz_sprite_batch get_sprite_batch(JNIEnv* env, jobject object)
{
    jclass class = (*env)->GetObjectClass(env, object);

    jfieldID width_field = (*env)->GetFieldID(env, class, "width", "I");
    jfieldID height_field = (*env)->GetFieldID(env, class, "height", "I");
    jfieldID size_field = (*env)->GetFieldID(env, class, "size", "I");
    jfieldID id_field = (*env)->GetFieldID(env, class, "id", "I");

    jint width = (*env)->GetIntField(env, object, width_field);
    jint height = (*env)->GetIntField(env, object, height_field);
    jint size = (*env)->GetIntField(env, object, size_field);
    jint id = (*env)->GetIntField(env, object, id_field);

    return (mz_sprite_batch)
    {
        .width = width,
        .height = height,
        .size = size,
        .id = id
    };
}

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_SpriteBatch_load(JNIEnv* env, jclass class, jobjectArray filepaths)
{
    const jsize length = (*env)->GetArrayLength(env, filepaths);
    const char* _filepaths[length];
    jstring strings[length];

    for (int i = 0; i < length; i++)
    {
        strings[i] = (jstring)((*env)->GetObjectArrayElement(env, filepaths, i));
         _filepaths[i] = (*env)->GetStringUTFChars(env, strings[i], NULL);

    }

    mz_sprite_batch batch = mz_load_sprite_batch(_filepaths, length);

    for (int i = 0; i < length; i++)
    {

        (*env)->ReleaseStringUTFChars(env, strings[i], _filepaths[i]);
        (*env)->DeleteLocalRef(env, strings[i]);
    }

    jmethodID ctor = (*env)->GetMethodID(env, class, "<init>", "(IIII)V");
    jobject jbatch = (*env)->NewObject(env, class, ctor, batch.width, batch.height, batch.size, batch.id);

    return jbatch;
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_SpriteBatch_bind(JNIEnv* env, jobject object, jobject applet, jbyte texture_unit)
{
    if (texture_unit < 0)
    {
        mz_log_status(LOG_STATUS_ERROR, "[JNI] :: textureUnit cannot be a negative number");
        return;
    }

    mz_sprite_batch batch = get_sprite_batch(env, object);
    mz_applet* _applet = get_applet(env, applet);
    mz_bind_sprite_batch(_applet, &batch, texture_unit);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_SpriteBatch_unload(JNIEnv* env, jobject object)
{
    jclass class = (*env)->GetObjectClass(env, object);

    jfieldID width_field = (*env)->GetFieldID(env, class, "width", "I");
    jfieldID height_field = (*env)->GetFieldID(env, class, "height", "I");
    jfieldID size_field = (*env)->GetFieldID(env, class, "size", "I");
    jfieldID id_field = (*env)->GetFieldID(env, class, "id", "I");

    jint width = (*env)->GetIntField(env, object, width_field);
    jint height = (*env)->GetIntField(env, object, height_field);
    jint size = (*env)->GetIntField(env, object, size_field);
    jint id = (*env)->GetIntField(env, object, id_field);

    mz_sprite_batch batch = (mz_sprite_batch)
    {
        .width = width,
        .height = height,
        .size = size,
        .id = id
    };

    mz_unload_sprite_batch(&batch);

    (*env)->SetIntField(env, object, width_field, 0);
    (*env)->SetIntField(env, object, height_field, 0);
    (*env)->SetIntField(env, object, size_field, 0);
    (*env)->SetIntField(env, object, id_field, 0);
}
