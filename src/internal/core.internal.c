#include "internal/core.internal.h"

MZcallback_keyinputfun mz_glfw_callback_hook_key	       =	NULL;
MZcallback_errorfun mz_glfw_callback_hook_error            =	NULL;
MZcallback_resizefun mz_glfw_callback_hook_window_resize   =	NULL;

void mz_glfw_callback_error(int error, const char* desc)
{
	log_status_formatted(STATUS_ERROR, "Internal Error (GLFW3): %s", desc);
	
	if (mz_glfw_callback_hook_error != NULL)
		mz_glfw_callback_hook_error(error, desc);
}

void mz_glfw_callback_key(GLFWwindow* handle, int key, int scan_code, int action, int mods)
{
	if (key == MUZZLE_DEFAULT_EXIT_KEY && action == GLFW_PRESS)
		glfwSetWindowShouldClose(handle, GL_TRUE);
	
	if (mz_glfw_callback_hook_window_resize != NULL)
		mz_glfw_callback_hook_key(
				(Applet*)(glfwGetWindowUserPointer(handle)),
				key, scan_code, action, mods
		);
}

MZ_API void mz_glfw_callback_window_resize(GLFWwindow* handle, int width, int height)
{
	Applet* applet = (Applet*)(glfwGetWindowUserPointer(handle));
	applet->width = width;
	applet->height = height;

	glViewport(0,0,width,height);
	
	if (mz_glfw_callback_hook_window_resize != NULL)
		mz_glfw_callback_hook_window_resize(
			(Applet*)(glfwGetWindowUserPointer(handle)),
			width, height
		);
}