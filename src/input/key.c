#include "input/key.h"

mz_boolean mz_key_pressed(mz_applet* applet, mz_key key)
{
	return glfwGetKey(applet->window, key) == GLFW_PRESS;
}

mz_boolean mz_key_released(mz_applet* applet, mz_key key)
{
	return glfwGetKey(applet->window, key) == GLFW_RELEASE;
}
