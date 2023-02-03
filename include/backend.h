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

#include <stdlib.h>
#include "memory.h"

#define MUZZLE_FALSE 0
#define MUZZLE_TRUE 1

#ifndef MUZZLE_RETAIN_LEGACY
    #define GLAD_GL_IMPLEMENTION
    #include "../deps/glad/include/glad/glad.h"
#endif

#ifdef MZ_DEPS_USE_GLOBAL
    #include <GLFW/glfw3.h>
#else
    #include "../deps/glfw/include/GLFW/glfw3.h"
#endif

#define MZ_ASSERT(condition, msg) if ((condition) == 0) \
{ \
fprintf(stderr, "Assertion '%s' failed in function '%s', more info: %s", #condition, __func__, msg); \
exit(-1); \
}

#define MZ_ASSERT_NO_MSG(condition) if ((condition) == 0) \
{ \
fprintf(stderr, "Assertion '%s' failed in function '%s'", #condition, __func__); \
exit(-1); \
}

#define MUZZLE_NULL (void*)(1)

#ifdef _WIN32
    // Include WinAPI if on windows. Required for MultiByteToWideChar
    #include "windows.h"

    #ifdef BUILD_LIBTYPE_SHARED
        #define MZ_API __declspec(dllexport)
    #elif defined(USE_LIBTYPE_SHARED)
        #define MZ_API __declspec(dllimport)
    #endif
#endif

#ifndef MZ_API
    #define MZ_API
#endif

#ifndef MZ_FONT_DEFAULT_SIZE
    #define MZ_FONT_DEFAULT_SIZE 32
#endif


#ifdef __cplusplus
    #define MZ_LITERAL(x) x
#else
    #define MZ_LITERAL(x) (x)
#endif

static void* __draw_pointer_ctx; // This pointer should only be used for drawing functions, like draw_rectangle. This pointer should be used for context data needed by the drawing functions
typedef GLFWwindow* MUZZLE_WINDOW;