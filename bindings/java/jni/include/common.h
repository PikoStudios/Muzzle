#ifndef MUZZLE_BINDINGS_JAVA_JNI_COMMON_H
#define MUZZLE_BINDINGS_JAVA_JNI_COMMON_H

#include <jni.h>
#include "core/applet.h"
#include "core/pipeline.h"
#include "core/shader.h"
#include "core/tint.h"

#define PTR_TO_JLONG(p) ((jlong)(((intptr_t)(p))))
#define JLONG_TO_PTR(p) ((intptr_t)(p))
#define JBOOLEAN(b) ((b) ? JNI_TRUE : JNI_FALSE)
#define UNUSED(a) ((void)(a))

// If you already have the class no purpose in looking it up again, use a get_*_with_cls

mz_applet* get_applet_with_cls(JNIEnv* env, jclass class, jobject obj);
mz_applet* get_applet(JNIEnv* env, jobject obj);

mz_shader get_shader_with_cls(JNIEnv* env, jclass class, jobject obj);
mz_shader get_shader(JNIEnv* env, jobject obj);

// TODO: Who else is going to need a shader pass???? Better to put it in the shader pass file and then the compiler will probably inline it too
mz_shader_pass get_shader_pass_with_cls(JNIEnv* env, jclass class, jobject obj);
mz_shader_pass get_shader_pass(JNIEnv* env, jobject obj);

mz_tint get_tint_with_cls(JNIEnv* env, jclass class, jobject obj);
mz_tint get_tint(JNIEnv* env, jobject obj);

mz_vertex_buffer* get_vertex_buffer(JNIEnv* env, jobject obj);

#endif // MUZZLE_BINDINGS_JAVA_JNI_COMMON_H
