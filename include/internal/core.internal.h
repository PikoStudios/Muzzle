#ifndef MUZZLE_CORE_INTERNAL_H
#define MUZZLE_CORE_INTERNAL_H

#include "../backend.h"
#include "../core/Error.h"
#include "../core/Applet.h"
#include "core/CallbackHook.h"

extern MZcallback_keyinputfun      mz_glfw_callback_hook_key;
extern MZcallback_errorfun         mz_glfw_callback_hook_error;
extern MZcallback_resizefun        mz_glfw_callback_hook_window_resize;

// GLFW Callbacks
MZ_API void mz_glfw_callback_error(int error, const char* desc);
MZ_API void mz_glfw_callback_key(GLFWwindow* handle, int key, int scan_code, int action, int mods);
MZ_API void mz_glfw_callback_window_resize(GLFWwindow* handle, int width, int height);

#endif // MUZZLE_CORE_INERNAL_H