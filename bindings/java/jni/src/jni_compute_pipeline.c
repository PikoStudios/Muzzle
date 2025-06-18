#include "../include/dev_pikostudios_muzzle_bridge_ComputePipeline.h"
#include "../include/common.h"
#include "core/shader.h"

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_ComputePipeline_create(JNIEnv* env, jclass class, jstring compute_shader, jboolean is_filepath, jobject sprite, jbyte texture_unit)
{
	const char* cs = (*env)->GetStringUTFChars(env, compute_shader, NULL);
	mz_sprite texture = (mz_sprite){0};

	if (sprite != NULL)
	{
    	jclass sprite_cls = (*env)->GetObjectClass(env, sprite);
    	jfieldID width_field = (*env)->GetFieldID(env, sprite_cls, "width", "I");
    	jfieldID height_field = (*env)->GetFieldID(env, sprite_cls, "height", "I");
    	jfieldID id_field = (*env)->GetFieldID(env, sprite_cls, "id", "I");

    	jint width = (*env)->GetIntField(env, sprite, width_field);
    	jint height = (*env)->GetIntField(env, sprite, height_field);
    	jint id = (*env)->GetIntField(env, sprite, id_field);

    	texture.width = width;
    	texture.height = height;
    	texture._id = id;
	}

	mz_sprite* tex = texture._id == 0 ? NULL : &texture;
	GLuint tex_id = tex == NULL ? 0 : texture._id;
	uint32_t tex_w = tex == NULL ? 0 : texture.width;
	uint32_t tex_h = tex == NULL ? 0 : texture.height;
	
	mz_compute_pipeline pipeline = mz_create_compute_pipeline(cs, is_filepath, tex, texture_unit);

	jmethodID ctor = (*env)->GetMethodID(env, class, "<init>", "(IIIIB)V");
	jobject jpipeline = (*env)->NewObject(env, class, ctor, pipeline.shader.pid, tex_id, tex_w, tex_h, texture_unit);

	(*env)->ReleaseStringUTFChars(env, compute_shader, cs);
	return jpipeline;
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_ComputePipeline_dispatch(JNIEnv* env, jobject object, jint work_groups_x, jint work_groups_y, jint work_groups_z)
{
	jclass class = (*env)->GetObjectClass(env, object);
	jfieldID shader_field = (*env)->GetFieldID(env, class, "shader", "Ldev/pikostudios/muzzle/bridge/Shader;");
	jfieldID texture_field = (*env)->GetFieldID(env, class, "texture", "Ldev/pikostudios/muzzle/bridge/Sprite;");
	jfieldID texture_unit_field = (*env)->GetFieldID(env, class, "textureUnit", "B");

	jobject shader = (*env)->GetObjectField(env, class, shader_field);
	jobject texture = (*env)->GetObjectField(env, class, texture_field);
	jbyte texture_unit = (*env)->GetByteField(env, class, texture_unit_field);

	jclass shader_class = (*env)->GetObjectClass(env, shader);
	jfieldID shader_id_field = (*env)->GetFieldID(env, shader_class, "id", "I");
	jint shader_id = (*env)->GetIntField(env, shader, shader_id_field);
	mz_shader _shader = (mz_shader){.pid = shader_id, .type = SHADER_TYPE_COMPUTE};
	
   	jclass texture_class = (*env)->GetObjectClass(env, texture);
   	jfieldID width_field = (*env)->GetFieldID(env, texture_class, "width", "I");
   	jfieldID height_field = (*env)->GetFieldID(env, texture_class, "height", "I");
   	jfieldID id_field = (*env)->GetFieldID(env, texture_class, "id", "I");

   	jint width = (*env)->GetIntField(env, texture, width_field);
   	jint height = (*env)->GetIntField(env, texture, height_field);
   	jint id = (*env)->GetIntField(env, texture, id_field);

   	mz_sprite _texture = (mz_sprite){._id = id, .width = width, .height = height};

	mz_compute_pipeline p = (mz_compute_pipeline){.shader = _shader, .texture = _texture, .texture_unit = texture_unit};

   	mz_dispatch_compute_pipeline(&p, work_groups_x, work_groups_y, work_groups_z);
}
