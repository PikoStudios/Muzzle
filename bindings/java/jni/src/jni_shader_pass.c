#include "../include/dev_pikostudios_muzzle_bridge_ShaderPass.h"
#include "../include/common.h"
#include "core/shader.h"

#define SHADER_PASS_CTOR_SIGNATURE "(Ldev/pikostudios/muzzle/bridge/Shader;III)V"

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_ShaderPass_create(JNIEnv* env, jclass class, jobject shader)
{
	mz_shader _shader = get_shader(env, shader);
	mz_shader_pass shader_pass = mz_create_shader_pass(_shader);

	jmethodID ctor = (*env)->GetMethodID(env, class, "<init>", SHADER_PASS_CTOR_SIGNATURE);
	jobject jshaderpass = (*env)->NewObject(env, class, ctor, shader, shader_pass.depth_texture_uniform_loc, shader_pass.screen_texture_uniform_loc, shader_pass.resolution_uniform_loc);

	return jshaderpass;
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_ShaderPass_use(JNIEnv* env, jobject object, jobject applet)
{
	mz_applet* _applet = get_applet(env, applet);
	mz_shader_pass shader_pass = get_shader_pass(env, object);

	mz_use_shader_pass(_applet, &shader_pass);
}
