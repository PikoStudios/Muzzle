#include "input/mouse.h"

mz_boolean mz_mouse_pressed(mz_applet* applet, mz_mouse_button button)
{
	return glfwGetMouseButton(applet->window, button) == GLFW_PRESS;
}

mz_boolean mz_mouse_released(mz_applet* applet, mz_mouse_button button)
{
	return glfwGetMouseButton(applet->window, button) == GLFW_RELEASE;
}

mz_vec2_d mz_get_mouse_position(mz_applet* applet)
{
	mz_vec2_d pos;
	glfwGetCursorPos(applet->window, &pos.x, &pos.y);
	
	return pos;
}

mz_vec2 mz_get_mouse_position_vec2(mz_applet* applet)
{
	double x,y;
	glfwGetCursorPos(applet->window, &x, &y);

	return (mz_vec2){(float)(x), (float)(y)};
}

double mz_get_mouse_x(mz_applet* applet)
{
	double x;
	glfwGetCursorPos(applet->window, &x, NULL);

	return x;
}

double mz_get_mouse_y(mz_applet* applet)
{
	double y;
	glfwGetCursorPos(applet->window, NULL, &y);

	return y;
}

float mz_get_mouse_xf(mz_applet* applet)
{
	return (float)(mz_get_mouse_x(applet));
}

float mz_get_mouse_yf(mz_applet* applet)
{
	return (float)(mz_get_mouse_y(applet));
}

void mz_set_cursor_state(mz_applet* applet, mz_cursor_state state)
{
	glfwSetInputMode(applet->window, GLFW_CURSOR, state);
}
