#ifndef MUZZLE_CORE_INTERNAL_H
#define MUZZLE_CORE_INTERNAL_H

#include "../backend.h"
#include "../core/Error.h"

// GLFW Callbacks
MZ_API void mz_glfw_callback_error(int error, const char* desc);
MZ_API void mz_glfw_callback_key(GLFWwindow* handle, int key, int scan_code, int action, int mods);

#endif // MUZZLE_CORE_INERNAL_H