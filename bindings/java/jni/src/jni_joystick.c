#include "backend.h"
#include "../include/dev_pikostudios_muzzle_bridge_Joystick.h"
#include "input/joystick.h"

#define NO_CONST_PTR_CAST(x) (void*)(x)

static inline mz_joystick get_joystick(JNIEnv* env, jobject joystick)
{
	jclass class = (*env)->GetObjectClass(env, joystick);
	jfieldID slot_field = (*env)->GetFieldID(env, class, "slot", "I");
	jint slot = (*env)->GetIntField(env, class, slot_field);

	return (mz_joystick){.slot = slot};
}

JNIEXPORT jboolean JNICALL Java_dev_pikostudios_muzzle_bridge_Joystick_exists(JNIEnv* env, jclass class, jint slot)
{
	MZ_UNUSED(env);
	MZ_UNUSED(class);

	return mz_joystick_exists(slot);
}

JNIEXPORT jobject JNICALL Java_dev_pikostudios_muzzle_bridge_Joystick__1open(JNIEnv* env, jclass class, jint slot)
{
	mz_joystick js = (mz_joystick){0};
	mz_boolean result = mz_open_joystick(&js, slot);

	if (!result)
	{
		return NULL;
	}

	jstring jname = (*env)->NewStringUTF(env, js.name);
	jstring jguid = (*env)->NewStringUTF(env, js.guid);

	jmethodID ctor = (*env)->GetMethodID(env, class, "<init>", "(IILjava/lang/String;Ljava/lang/String;)V");
	jobject jjoystick = (*env)->NewObject(env, class, ctor, js.slot, js.is_gamepad, jname, jguid);

	return jjoystick;
}

JNIEXPORT jboolean JNICALL Java_dev_pikostudios_muzzle_bridge_Joystick__1queryState(JNIEnv* env, jobject joystick, jobject state)
{
	mz_joystick js = get_joystick(env, joystick);
	
	jclass state_class = (*env)->GetObjectClass(env, state);

	jmethodID open_method = (*env)->GetMethodID(env, state_class, "open", "(Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;)V");

	mz_joystick_state js_state = (mz_joystick_state){0};
	mz_boolean result = mz_query_joystick_state(&js, &js_state);

	if (!result)
	{
		return MUZZLE_FALSE;
	}

	_Static_assert(sizeof(mz_joystick_hat_state) == sizeof(uint8_t), "mz_joystick_hat_state is not sizeof uint8_t, please use a compiler which supports typed enum GCC extensions");

	jobject axes_buffer = (*env)->NewDirectByteBuffer(env, NO_CONST_PTR_CAST(js_state.axes), js_state.axes_count * sizeof(float));
	jobject buttons_buffer = (*env)->NewDirectByteBuffer(env, NO_CONST_PTR_CAST(js_state.buttons), js_state.buttons_count * sizeof(mz_boolean));
	jobject hats_buffer = (*env)->NewDirectByteBuffer(env, NO_CONST_PTR_CAST(js_state.hats), js_state.hats_count * sizeof(uint8_t));

	(*env)->CallVoidMethod(env, state, open_method, axes_buffer, buttons_buffer, hats_buffer);

	return MUZZLE_TRUE;
}
