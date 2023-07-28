#include "core/CallbackHook.h"
#include "internal/core.internal.h"

void muzzle_register_callback(uint8_t target, union callback_hook_union callback)
{
	switch(target)
	{
	case MUZZLE_CALLBACK_HOOK_KEY_INPUT:
		mz_glfw_callback_hook_key = callback.key_input_fptr;
		break;
	
	case MUZZLE_CALLBACK_HOOK_ERROR:
		mz_glfw_callback_hook_error = callback.error_fptr;
		break;
	
	case MUZZLE_CALLBACK_HOOK_REISZE:
		mz_glfw_callback_hook_window_resize = callback.resize_fptr;
		break;
	
	default:
		log_status(STATUS_ERROR, "Unknown callback hook target");
		printf("Callback hook target = %hu\n", target);
		break;
	}
}