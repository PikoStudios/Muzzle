#include "../include/dev_pikostudios_muzzle_bridge_DirectShader.h"
#include "../include/common.h"
#include "core/shader.h"

#define DIRECT_SHADER_CTOR_SIGNATURE "(Ldev/pikostudios/muzzle/bridge/Shader;I)V"

static mz_direct_shader get_direct_shader(JNIEnv* env, jobject obj)
{
	jclass class = (*env)->GetObjectClass(env, obj);

	jfieldID shader_id_field = (*env)->GetFieldID(env, class, "shaderIDCache", "I");
	jfieldID target_field = (*env)->GetFieldID(env, class, "target", "I");

	jint shader_id = (*env)->GetIntField(env, obj, shader_id_field);
	jint target = (*env)->GetIntField(env, obj, target_field);

	return (mz_direct_shader)
	{
		.shader = (mz_shader){.pid = shader_id},
		.target = target
	};
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_DirectShader_begin(JNIEnv* env, jobject object, jobject applet)
{
	mz_applet* _applet = get_applet(env, applet);
	mz_direct_shader direct_shader = get_direct_shader(env, object);

	mz_begin_direct_shader(_applet, direct_shader);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_DirectShader_end(JNIEnv* env, jobject object, jobject applet)
{
	mz_applet* _applet = get_applet(env, applet);
	mz_direct_shader direct_shader = get_direct_shader(env, object);

	mz_end_direct_shader(_applet, direct_shader);
}

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_DirectShader__1create(JNIEnv* env, jclass class, jobject shader, jint target)
{
	mz_shader _shader = get_shader(env, shader);
	mz_direct_shader direct_shader = mz_create_direct_shader(target, _shader); // we can blindly trust target here
	
	jmethodID ctor = (*env)->GetMethodID(env, class, "<init>", DIRECT_SHADER_CTOR_SIGNATURE);
	jobject jdirectshader = (*env)->NewObject(env, class, ctor, shader, direct_shader.target);

	return jdirectshader;
}
