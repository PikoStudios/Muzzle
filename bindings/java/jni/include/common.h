#ifndef MUZZLE_BINDINGS_JAVA_JNI_COMMON_H
#define MUZZLE_BINDINGS_JAVA_JNI_COMMON_H

#include <jni.h>
#include "core/applet.h"

#define PTR_TO_JLONG(p) ((jlong)(((intptr_t)(p))))
#define JLONG_TO_PTR(p) ((intptr_t)(p))
#define JBOOLEAN(b) ((b) ? JNI_TRUE : JNI_FALSE)

mz_applet* get_applet(JNIEnv* env, jobject obj);

#endif // MUZZLE_BINDINGS_JAVA_JNI_COMMON_H
