#ifndef MUZZLE_CORE_INTERNAL_H
#define MUZZLE_CORE_INTERNAL_H

#include "../backend.h"
#include "../core/Error.h"
#include "../core/Applet.h"

// GLFW Callbacks
MZ_API void mz_glfw_callback_error(int error, const char* desc);
MZ_API void mz_glfw_callback_key(GLFWwindow* handle, int key, int scan_code, int action, int mods);
MZ_API void mz_glfw_callback_window_resize(GLFWwindow* handle, int width, int height);

#endif // MUZZLE_CORE_INERNAL_H