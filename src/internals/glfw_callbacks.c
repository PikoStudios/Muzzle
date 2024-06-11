#include "internals/glfw_callbacks.h"
#include "core/applet.h"
#include "core/logging.h"

void internals_glfw_callback_error(int error, const char* desc)
{
	mz_log_status_formatted(LOG_STATUS_ERROR, "Internal Error (GLFW3): %s", desc);
}

void internals_glfw_callback_key(GLFWwindow* handle, int key, int scan_code, int action, int mods)
{
	if (key == MUZZLE_EXIT_KEY && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(handle, GL_TRUE);
	}
}

void internals_glfw_callback_window_resize(GLFWwindow* window, int width, int height)
{
	mz_applet* applet = (mz_applet*)(glfwGetWindowUserPointer(window));
	applet->width = width;
	applet->height = height;

	glViewport(0,0,width,height);

	//if (applet->quad_renderer.locs_valid)
	//{
	//	glUniform2f(applet->quad_renderer.loc_uViewportResolution, width, height);
	//}
}
