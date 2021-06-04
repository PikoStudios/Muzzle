#include "core/Input.h"

int key_up(Applet *applet, KeyInput key)
{
    if (glfwGetKey(applet->window_handle, key) == GLFW_RELEASE) return 1;
    else return 0;
}
int key_down(Applet *applet, KeyInput key)
{
    if (glfwGetKey(applet->window_handle, key) == GLFW_PRESS) return 1;
    else return 0;
}

int mouse_up(Applet *applet, MouseInput button)
{
    if (glfwGetMouseButton(applet->window_handle, button) == GLFW_RELEASE) return 1;
    else return 0;
}
int mouse_down(Applet *applet, MouseInput button)
{
    if (glfwGetMouseButton(applet->window_handle, button) == GLFW_PRESS) return 1;
    else return 0;
}
