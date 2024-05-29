#ifndef MUZZLE_INTERNALS_GLFW_CALLBACKS
#define MUZZLE_INTERNALS_GLFW_CALLBACKS

#include "../backend.h"

MZ_API void internals_glfw_callback_error(int error, const char* desc);
MZ_API void internals_glfw_callback_key(GLFWwindow* handle, int ket, int scan_code, int action, int mods);
MZ_API void internals_glfw_callback_window_resize(GLFWwindow* window, int width, int height);

#endif // MUZZLE_INTERNALS_GLFW_CALLBACKS
