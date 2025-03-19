#include "../include/dev_pikostudios_muzzle_bridge_Applet.h"
#include "core/applet.h"
#include "core/logging.h"
#include "core/memory.h"

#define PTR_TO_JLONG(p) ((jlong)(((intptr_t)(p))))
#define JLONG_TO_PTR(p) ((intptr_t)(p))
#define JBOOLEAN(b) ((b) ? JNI_TRUE : JNI_FALSE)

static JNIEnv* __applet_start_jnienv;
static jobject __applet_start_callback;

static mz_applet* get_applet(JNIEnv* env, jobject obj)
{
    jclass cls = (*env)->GetObjectClass(env, obj);
    jfieldID native_pointer_field = (*env)->GetFieldID(env, cls, "nativePointer", "J");
    jlong native_pointer = (*env)->GetLongField(env, obj, native_pointer_field);

    return (mz_applet*)(JLONG_TO_PTR(native_pointer));
}

static void applet_dispatch(mz_applet* applet)
{
    jclass callback_class = (*__applet_start_jnienv)->GetObjectClass(__applet_start_jnienv, __applet_start_callback);
    jmethodID callback_method = (*__applet_start_jnienv)->GetMethodID(__applet_start_jnienv, callback_class, "invoke", "(Ldev/pikostudios/muzzle/bridge/Applet;)V");

    (*__applet_start_jnienv)->CallVoidMethod(__applet_start_jnienv, __applet_start_callback, callback_method);
}

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_Applet_initialize(JNIEnv* env, jclass class, jstring window_title, jint width, jint height, jint flags)
{
    const char* title = (*env)->GetStringUTFChars(env, window_title, NULL);

    mz_applet* applet = MZ_MALLOC(sizeof(mz_applet));

    if (applet == NULL)
    {
        mz_log_status(LOG_STATUS_FATAL_ERROR, "[JNI] :: Could not initialize memory for applet object");
    }
    
    *applet = mz_initialize_applet(title, width, height, flags);

    jmethodID ctor = (*env)->GetMethodID(env, class, "<init>", "(Ljava/lang/String;JJ)V");
    jobject japplet = (*env)->NewObject(env, class, ctor, window_title, PTR_TO_JLONG(applet), PTR_TO_JLONG(title));

    return japplet;
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Applet_start(JNIEnv* env, jobject object, jobject callback)
{
    mz_applet* applet = get_applet(env, object);
    __applet_start_jnienv = env;
    __applet_start_callback = callback;
    
    mz_start_applet(applet, applet_dispatch);
}


JNIEXPORT jboolean JNICALL Java_dev_pikostudios_muzzle_bridge_Applet_keepRunning(JNIEnv* env, jobject object)
{
    mz_applet* applet = get_applet(env, object);
    return JBOOLEAN(mz_keep_applet(applet));
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Applet_terminate(JNIEnv* env, jobject object)
{
    mz_applet* applet = get_applet(env, object);
    jclass cls = (*env)->GetObjectClass(env, object);
    
    jfieldID title_pointer_field = (*env)->GetFieldID(env, cls, "titlePointer", "J");
    jfieldID applet_pointer_field = (*env)->GetFieldID(env, cls, "nativePointer", "J");
    jfieldID title_object_field = (*env)->GetFieldID(env, cls, "title", "Ljava/lang/String;");
    
    jlong title_pointer = (*env)->GetLongField(env, object, title_pointer_field);
    jstring title_object = (jstring)((*env)->GetObjectField(env, object, title_object_field));
    
    const char* title = (char*)(JLONG_TO_PTR(title_pointer));

    (*env)->ReleaseStringUTFChars(env, title_object, title);
    mz_terminate_applet(applet);

    MZ_FREE(applet);

    (*env)->SetLongField(env, object, title_pointer_field, 0L);
    (*env)->SetLongField(env, object, applet_pointer_field, 0L);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Applet_updateWindowTitle(JNIEnv* env, jobject object, jstring title)
{
    mz_applet* applet = get_applet(env, object);
    jclass cls = (*env)->GetObjectClass(env, object);

    jfieldID title_pointer_field = (*env)->GetFieldID(env, cls, "titlePointer", "J");
    jfieldID title_object_field = (*env)->GetFieldID(env, cls, "title", "Ljava/lang/String;");

    jlong title_pointer = (*env)->GetLongField(env, object, title_pointer_field);
    jstring title_object = (jstring)((*env)->GetObjectField(env, object, title_object_field));

    const char* old_title = (char*)(JLONG_TO_PTR(title_pointer));

    (*env)->ReleaseStringUTFChars(env, title_object, old_title);
    (*env)->SetObjectField(env, object, title_object_field, title);

    const char* new_title = (*env)->GetStringUTFChars(env, title, NULL);

    (*env)->SetLongField(env, object, title_pointer_field, PTR_TO_JLONG(new_title));
}

JNIEXPORT jint JNICALL Java_dev_pikostudios_muzzle_bridge_Applet_getWidth(JNIEnv* env, jobject object)
{
    mz_applet* applet = get_applet(env, object);
    return applet->width;
}

JNIEXPORT jint JNICALL Java_dev_pikostudios_muzzle_bridge_Applet_getHeight(JNIEnv* env, jobject object)
{
    mz_applet* applet = get_applet(env, object);
    return applet->height;
}

JNIEXPORT jdouble JNICALL Java_dev_pikostudios_muzzle_bridge_Applet_getDeltaTime(JNIEnv* env, jobject object)
{
    mz_applet* applet = get_applet(env, object);
    return applet->delta_time;
}
