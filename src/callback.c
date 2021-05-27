#include "core/callback.h"

void callback_key(GLFWwindow *handle, int key, int scan_code, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(handle, GL_TRUE);
}