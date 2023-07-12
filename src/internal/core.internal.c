#include "internal/core.internal.h"

void mz_glfw_callback_error(int error, const char* desc)
{
	log_status_formatted(STATUS_ERROR, "Internal Error (GLFW3): %s", desc);
}

void mz_glfw_callback_key(GLFWwindow* handle, int key, int scan_code, int action, int mods)
{
	if (key == MUZZLE_DEFAULT_EXIT_KEY && action == GLFW_PRESS)
		glfwSetWindowShouldClose(handle, GL_TRUE);
}

MZ_API void mz_glfw_callback_window_resize(GLFWwindow* handle, int width, int height)
{
	Applet* applet = (Applet*)(glfwGetWindowUserPointer(handle));
	applet->width = width;
	applet->height = height;

	glViewport(0,0,width,height);
}