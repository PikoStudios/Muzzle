#pragma once

#if defined(__EMSCRIPTEN__)
    #define GLFW_INCLUDE_ES2
#endif


#ifdef MUZZLE_ALLOW_BUFFER_HIGH
    #define MAX_BUFFERS 8
    #define BUFFER_LENGTH 2048
#else
    #define MAX_BUFFERS 4
    #define BUFFER_LENGTH 1024
#endif

#define MUZZLE_FALSE 0
#define MUZZLE_TRUE 1

#ifdef MZ_DEPS_USE_GLOBAL
    #include <GLFW/glfw3.h>
#else
    #include "../deps/glfw/include/GLFW/glfw3.h"
#endif

#ifdef _WIN32
    // Include WinAPI if on windows. Required for MultiByteToWideChar
    #include "windows.h"
#endif

//#ifdef __unix__
//    #include <X11/Xlib.h>
//    #include <X11/Xutil.h>
//	#include <X11/Xos.h>
//    #define MZ_AUDIO_FORCE_X11
//#endif

#ifdef __cplusplus
    #define MZ_LITERAL(x) x
#else
    #define MZ_LITERAL(x) (x)
#endif

typedef GLFWwindow* MUZZLE_WINDOW;
