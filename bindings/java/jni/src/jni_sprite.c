#include "../include/dev_pikostudios_muzzle_bridge_Sprite.h"
#include "core/logging.h"
#include "core/memory.h"
#include "jni.h"
#include "primitives/sprite.h"
#include "../include/common.h"
#include <string.h>

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


JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_Sprite_create(JNIEnv* env, jclass class, jint width, jint height, jint wrapping_mode, jint min_filter, jint mag_filter, jint format, jbyteArray data)
{
    mz_sprite_wrapping_mode wm = 0;
    mz_sprite_filter_mode minf = 0, magf = 0;
    mz_sprite_format fm = 0;

    // TODO: wow lots of switch statements oh well
    switch (wrapping_mode)
    {
    case 0:
        wm = SPRITE_WRAPPING_MODE_REPEAT;
        break;

    case 1:
        wm = SPRITE_WRAPPING_MODE_MIRRORED_REPEAT;
        break;

    case 2:
        wm = SPRITE_WRAPPING_MODE_CLAMP_TO_EDGE;
        break;
    }

    switch (min_filter)
    {
    case 0:
        minf = SPRITE_FILTER_MODE_NEAREST;
        break;

    case 1:
        minf = SPRITE_FILTER_MODE_LINEAR;
        break;
    }
    
    switch (mag_filter)
    {
    case 0:
        magf = SPRITE_FILTER_MODE_NEAREST;
        break;

    case 1:
        magf = SPRITE_FILTER_MODE_LINEAR;
        break;
    }

    switch (format)
    {
    case 0:
        fm = SPRITE_FORMAT_RGBA8;
        break;

    case 1:
        fm = SPRITE_FORMAT_RGBA32F;
        break;
    }

    // TODO: this is really dumb but i can't be bothered to fix rn, why are we only allowing bytes to be passed if RGBA32F is an option lol. ill fix later
    jbyte* bytes = NULL;
    
    if (data != NULL)
    {
        bytes = (*env)->GetByteArrayElements(env, data, NULL);
    }
    
    mz_sprite sprite = mz_create_sprite(width, height, wm, minf, magf, fm, bytes);
    (*env)->ReleaseByteArrayElements(env, data, bytes, JNI_ABORT);

    jmethodID ctor = (*env)->GetMethodID(env, class, "<init>", "(III)V");
    jobject jsprite = (*env)->NewObject(env, class, ctor, sprite.width, sprite.height, sprite._id);

    return jsprite;
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Sprite_draw(JNIEnv* env, jobject object, jobject applet, jfloat x, jfloat y, jobject tint)
{
    jclass class = (*env)->GetObjectClass(env, object);
    jfieldID width_field = (*env)->GetFieldID(env, class, "width", "I");
    jfieldID height_field = (*env)->GetFieldID(env, class, "height", "I");
    jfieldID id_field = (*env)->GetFieldID(env, class, "id", "I");

    jint width = (*env)->GetIntField(env, object, width_field);
    jint height = (*env)->GetIntField(env, object, height_field);
    jint id = (*env)->GetIntField(env, object, id_field);

    mz_sprite sprite = (mz_sprite){width, height, id};

    mz_applet* _applet = get_applet(env, applet);
    mz_tint _tint = get_tint(env, tint);

    mz_draw_sprite(_applet, &sprite, x, y, _tint);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Sprite_drawScaled(JNIEnv* env, jobject object, jobject applet, jfloat x, jfloat y, jfloat scale, jobject tint)
{
    jclass class = (*env)->GetObjectClass(env, object);
    jfieldID width_field = (*env)->GetFieldID(env, class, "width", "I");
    jfieldID height_field = (*env)->GetFieldID(env, class, "height", "I");
    jfieldID id_field = (*env)->GetFieldID(env, class, "id", "I");

    jint width = (*env)->GetIntField(env, object, width_field);
    jint height = (*env)->GetIntField(env, object, height_field);
    jint id = (*env)->GetIntField(env, object, id_field);

    mz_sprite sprite = (mz_sprite){width, height, id};

    mz_applet* _applet = get_applet(env, applet);
    mz_tint _tint = get_tint(env, tint);

    mz_draw_sprite_scaled(_applet, &sprite, x, y, scale, _tint);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Sprite_drawResized(JNIEnv* env, jobject object, jobject applet, jfloat x, jfloat y, jint w, jint h, jobject tint)
{
    jclass class = (*env)->GetObjectClass(env, object);
    jfieldID width_field = (*env)->GetFieldID(env, class, "width", "I");
    jfieldID height_field = (*env)->GetFieldID(env, class, "height", "I");
    jfieldID id_field = (*env)->GetFieldID(env, class, "id", "I");

    jint width = (*env)->GetIntField(env, object, width_field);
    jint height = (*env)->GetIntField(env, object, height_field);
    jint id = (*env)->GetIntField(env, object, id_field);

    mz_sprite sprite = (mz_sprite){width, height, id};

    mz_applet* _applet = get_applet(env, applet);
    mz_tint _tint = get_tint(env, tint);

    mz_draw_sprite_resized(_applet, &sprite, x, y, w, h, _tint);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Sprite_bind(JNIEnv* env, jobject object, jobject applet, jbyte unit)
{
    jclass class = (*env)->GetObjectClass(env, object);
    jfieldID width_field = (*env)->GetFieldID(env, class, "width", "I");
    jfieldID height_field = (*env)->GetFieldID(env, class, "height", "I");
    jfieldID id_field = (*env)->GetFieldID(env, class, "id", "I");

    jint width = (*env)->GetIntField(env, object, width_field);
    jint height = (*env)->GetIntField(env, object, height_field);
    jint id = (*env)->GetIntField(env, object, id_field);

    mz_sprite sprite = (mz_sprite){width, height, id};

    mz_applet* _applet = get_applet(env, applet);

    mz_bind_sprite(_applet, &sprite, unit);
}

JNIEXPORT jbyteArray JNICALL Java_dev_pikostudios_muzzle_bridge_Sprite_getPixels(JNIEnv* env, jobject object)
{
    jclass class = (*env)->GetObjectClass(env, object);
    jfieldID width_field = (*env)->GetFieldID(env, class, "width", "I");
    jfieldID height_field = (*env)->GetFieldID(env, class, "height", "I");
    jfieldID id_field = (*env)->GetFieldID(env, class, "id", "I");

    jint width = (*env)->GetIntField(env, object, width_field);
    jint height = (*env)->GetIntField(env, object, height_field);
    jint id = (*env)->GetIntField(env, object, id_field);

    mz_sprite sprite = (mz_sprite){width, height, id};

    size_t size = mz_read_sprite_pixels(&sprite, NULL, 0);
    unsigned char* data = MZ_MALLOC(size * sizeof(unsigned char));

    if (data == NULL)
    {
        mz_log_status(LOG_STATUS_FATAL_ERROR, "[JNI] :: Failed to allocate memory for sprite pixels");
    }

    mz_read_sprite_pixels(&sprite, data, size);

    jbyteArray bytes = (*env)->NewByteArray(env, size);

    if (bytes == NULL)
    {
        mz_log_status(LOG_STATUS_FATAL_ERROR, "[JNI] :: Failed to allocate byte array for sprite pixels");
    }

    (*env)->SetByteArrayRegion(env, bytes, 0, size, (jbyte*)(data));
    MZ_FREE(data);

    return bytes;
}
