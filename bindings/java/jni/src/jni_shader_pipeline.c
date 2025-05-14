#include "../include/dev_pikostudios_muzzle_bridge_ShaderPipeline.h"
#include "../include/common.h"
#include "core/logging.h"
#include "core/shader.h"

#ifdef _WIN32
	#define STACKALLOC(s) _alloca(s)
#else
	#include <alloca.h>
	#define STACKALLOC(s) alloca(s)
#endif

#define NOP()

static mz_shader_pipeline get_pipeline(JNIEnv* env, jobject object)
{
	jclass cls = (*env)->GetObjectClass(env, object);

	jfieldID pid_field = (*env)->GetFieldID(env, cls, "pid", "I");
	jfieldID vao_field = (*env)->GetFieldID(env, cls, "vao", "I");
	jfieldID vbo_field = (*env)->GetFieldID(env, cls, "vbo", "I");
	jfieldID primitive_type_field = (*env)->GetFieldID(env, cls, "primitiveType", "I");

	mz_shader_pipeline p = (mz_shader_pipeline){0};
	p.shader.pid = (*env)->GetIntField(env, object, pid_field);
	p.vao = (*env)->GetIntField(env, object, vao_field);
	p.vbo = (*env)->GetIntField(env, object, vbo_field);
	p.primitive_type = (*env)->GetIntField(env, object, primitive_type_field);

	return p;
}

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_ShaderPipeline_create(
	JNIEnv* env,
	jclass class,
	jint v_primitive_type,
	jfloatArray v_vertices,
	jstring v_source,
	jboolean v_sourcefilepath,
	jobjectArray v_attributes,
	jstring f_source,
	jboolean f_sourcefilepath,
	jstring g_source,
	jboolean g_sourcefilepath)
{
	mz_shader_pipeline_descriptor d = (mz_shader_pipeline_descriptor){0};

	switch (v_primitive_type)
	{
	case dev_pikostudios_muzzle_bridge_ShaderPipeline_PRIMITIVE_TYPE_TRIANGLE:
		d.vertex.primitive_type = SHADER_COMPONENT_VERTEX_PRIMITIVE_TYPE_TRIANGLE;
		break;

	case dev_pikostudios_muzzle_bridge_ShaderPipeline_PRIMITIVE_TYPE_TRIANGLE_STRIP:
		d.vertex.primitive_type = SHADER_COMPONENT_VERTEX_PRIMITIVE_TYPE_TRIANGLE_STRIP;
		break;

	case dev_pikostudios_muzzle_bridge_ShaderPipeline_PRIMITIVE_TYPE_POINT:
		d.vertex.primitive_type = SHADER_COMPONENT_VERTEX_PRIMITIVE_TYPE_POINT;
		break;

	default:
		mz_log_status_formatted(LOG_STATUS_FATAL_ERROR, "[JNI] :: Unknown primitive type %d", v_primitive_type);
		break;
	}
	
	d.vertex.source_type = (v_sourcefilepath) ? SHADER_COMPONENT_SOURCE_TYPE_FILEPATH : SHADER_COMPONENT_SOURCE_TYPE_SOURCE_CODE;
	d.vertex.source = (*env)->GetStringUTFChars(env, v_source, NULL);
	d.fragment.source_type = (f_sourcefilepath) ? SHADER_COMPONENT_SOURCE_TYPE_FILEPATH : SHADER_COMPONENT_SOURCE_TYPE_SOURCE_CODE;
	d.fragment.source = (*env)->GetStringUTFChars(env, f_source, NULL);
	d.geometry.source_type = (g_sourcefilepath) ? SHADER_COMPONENT_SOURCE_TYPE_FILEPATH : SHADER_COMPONENT_SOURCE_TYPE_SOURCE_CODE;
	d.geometry.source = (*env)->GetStringUTFChars(env, g_source, NULL);

	d.vertex.vertices = (*env)->GetFloatArrayElements(env, v_vertices, NULL);
	d.vertex.vertices_size = (*env)->GetArrayLength(env, v_vertices);
	
	jsize attrs_len = (*env)->GetArrayLength(env, v_attributes);

	if (attrs_len == 0)
	{
		goto skip_attrs;
	}
	
	mz_shader_component_vertex_attribute attrs = (mz_shader_component_vertex_attribute){0};
	mz_shader_component_vertex_attribute* attr = &attrs;
	d.vertex.attributes = &attrs;
	
	jobject refattr = (*env)->GetObjectArrayElement(env, v_attributes, 0);
	jclass cls = (*env)->GetObjectClass(env, refattr);
	(*env)->DeleteLocalRef(env, refattr);
	
	jfieldID index_field = (*env)->GetFieldID(env, cls, "index", "I");
	jfieldID size_field = (*env)->GetFieldID(env, cls, "size", "I");
	jfieldID normalized_field = (*env)->GetFieldID(env, cls, "normalized", "Z");
	jfieldID stride_field = (*env)->GetFieldID(env, cls, "stride", "I");
	jfieldID offset_field = (*env)->GetFieldID(env, cls, "offset", "I");

	for (int i = 0; i < attrs_len; i++)
	{
		jobject attribute = (*env)->GetObjectArrayElement(env, v_attributes, i);
		
		attr->index = (*env)->GetIntField(env, attribute, index_field);
		attr->size = (*env)->GetIntField(env, attribute, size_field);
		attr->normalized = (*env)->GetBooleanField(env, attribute, normalized_field);
		attr->stride = (*env)->GetIntField(env, attribute, stride_field);
		attr->offset = (*env)->GetIntField(env, attribute, offset_field);
		attr->next = NULL;

		if (i < attrs_len - 1)
		{
			attr->next = STACKALLOC(sizeof(mz_shader_component_vertex_attribute));
			attr = attr->next;
		}

		(*env)->DeleteLocalRef(env, attribute);
	}

skip_attrs:
	NOP(); // Decl. after label is only a C23 extension
	mz_shader_pipeline pipeline = mz_create_shader_pipeline(&d);

	jmethodID ctor = (*env)->GetMethodID(env, class, "<init>", "(IIII)V");
	jobject jpipeline = (*env)->NewObject(env, class, ctor, pipeline.shader.pid, pipeline.vao, pipeline.vbo, pipeline.primitive_type);
	
	(*env)->ReleaseFloatArrayElements(env, v_vertices, d.vertex.vertices, JNI_ABORT);
	(*env)->ReleaseStringUTFChars(env, v_source, d.vertex.source);
	(*env)->ReleaseStringUTFChars(env, f_source, d.fragment.source);

	if (d.geometry.source != NULL)
	{
		(*env)->ReleaseStringUTFChars(env, g_source, d.geometry.source);
	}

	return jpipeline;
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_ShaderPipeline_draw(JNIEnv* env, jobject object, jfloatArray vertices, jint start, jint end)
{
	mz_shader_pipeline pipeline = get_pipeline(env, object);

	float* verts = NULL;
	size_t verts_size = 0;

	if (vertices != NULL)
	{
		verts = (*env)->GetFloatArrayElements(env, vertices, NULL);
		verts_size = (*env)->GetArrayLength(env, vertices);
	}

	mz_draw_shader_pipeline(pipeline, verts, verts_size, start, end);

	if (vertices != NULL)
	{
		(*env)->ReleaseFloatArrayElements(env, vertices, verts, JNI_ABORT);
	}
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_ShaderPipeline_unload(JNIEnv* env, jobject object)
{
	jclass cls = (*env)->GetObjectClass(env, object);

	jfieldID pid_field = (*env)->GetFieldID(env, cls, "pid", "I");
	jfieldID vao_field = (*env)->GetFieldID(env, cls, "vao", "I");
	jfieldID vbo_field = (*env)->GetFieldID(env, cls, "vbo", "I");
	jfieldID primitive_type_field = (*env)->GetFieldID(env, cls, "primitiveType", "I");

	mz_shader_pipeline p = (mz_shader_pipeline){0};
	p.shader.pid = (*env)->GetIntField(env, object, pid_field);
	p.vao = (*env)->GetIntField(env, object, vao_field);
	p.vbo = (*env)->GetIntField(env, object, vbo_field);
	p.primitive_type = (*env)->GetIntField(env, object, primitive_type_field);
	
	mz_unload_shader_pipeline(&p);

	(*env)->SetIntField(env, object, pid_field, 0);
	(*env)->SetIntField(env, object, vao_field, 0);
	(*env)->SetIntField(env, object, vbo_field, 0);
	(*env)->SetIntField(env, object, primitive_type_field, 0);
}
