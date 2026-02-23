#include "../include/dev_pikostudios_muzzle_bridge_VertexBuffer.h"
#include "../include/common.h"
#include "core/pipeline.h"

#ifdef _WIN32
	#include <malloc.h>
#else
	#include <alloca.h>
#endif

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_VertexBuffer_create(JNIEnv* env, jclass class, jint topology_type, jobjectArray attributes_arr)
{
	mz_vertex_primitive_topology_type topology;

	switch (topology_type)
	{
		case 0: topology = VERTEX_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE; break;
		case 1: topology = VERTEX_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE_STRIP; break;
		case 2: topology = VERTEX_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE_FAN; break;
		case 3: topology = VERTEX_PRIMITIVE_TOPOLOGY_TYPE_POINT; break;
		case 4: topology = VERTEX_PRIMITIVE_TOPOLOGY_TYPE_LINES; break;
		default: __builtin_unreachable();
	}

	const jsize attributes_count = (*env)->GetArrayLength(env, attributes_arr);
	mz_vertex_attribute_descriptor* attributes = NULL;

	if (attributes_count != 0)
	{
		attributes = alloca(sizeof(mz_vertex_attribute_descriptor) * attributes_count); // using alloca because small enough for stack alloc, but VLAs are freed when out of scope

		jobject attribute_obj = (*env)->GetObjectArrayElement(env, attributes_arr, 0);
		jclass attribute_class = (*env)->GetObjectClass(env, attribute_obj);
		
		jfieldID attr_size_field_id = (*env)->GetFieldID(env, attribute_class, "size", "B");
		jfieldID attr_type_ordinal_field_id = (*env)->GetFieldID(env, attribute_class, "typeOrdinal", "I");
	
		for (jsize i = 0; i < attributes_count; i++)
		{
			if (i > 0)
			{
				attribute_obj = (*env)->GetObjectArrayElement(env, attributes_arr, i);
			}
			
			jbyte size = (*env)->GetByteField(env, attribute_obj, attr_size_field_id);
			jint type_ordinal = (*env)->GetIntField(env, attribute_obj, attr_type_ordinal_field_id);

			attributes[i].size = size;

			switch (type_ordinal)
			{
				case 0: attributes[i].type = VERTEX_ATTRIBUTE_TYPE_BYTE; break;
				case 1: attributes[i].type = VERTEX_ATTRIBUTE_TYPE_UNSIGNED_BYTE; break;
				case 2: attributes[i].type = VERTEX_ATTRIBUTE_TYPE_SHORT; break;
				case 3: attributes[i].type = VERTEX_ATTRIBUTE_TYPE_UNSIGNED_SHORT; break;
				case 4: attributes[i].type = VERTEX_ATTRIBUTE_TYPE_INT; break;
				case 5: attributes[i].type = VERTEX_ATTRIBUTE_TYPE_UNSIGNED_INT; break;
				case 6: attributes[i].type = VERTEX_ATTRIBUTE_TYPE_HALF_FLOAT; break;
				case 7: attributes[i].type = VERTEX_ATTRIBUTE_TYPE_FLOAT; break;
				case 8: attributes[i].type = VERTEX_ATTRIBUTE_TYPE_DOUBLE; break;
				default: __builtin_unreachable();
			}

			(*env)->DeleteLocalRef(env, attribute_obj);
		}
	}

	mz_vertex_buffer buffer = mz_create_vertex_buffer(topology, attributes, attributes_count);

	
}
