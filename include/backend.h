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

#ifndef MZ_MALLOC
    #define MZ_MALLOC(size)         malloc(size)
#endif

#ifndef MZ_CALLOC
    #define MZ_CALLOC(num, size)    calloc(num, size)
#endif

#ifndef MZ_FREE
    #define MZ_FREE(ptr)            free(ptr)
#endif

#ifndef MZ_REALLOC
    #define MZ_REALLOC(ptr, size)   realloc(ptr, size)
#endif

#define MUZZLE_FALSE 0
#define MUZZLE_TRUE 1

#ifdef MZ_DEPS_USE_GLOBAL
    #include <GLFW/glfw3.h>
#else
    #include "../deps/glfw/include/GLFW/glfw3.h"
#endif

// TODO: When modern pipeline is usable, remember to remove this line
#include "../deps/glad/include/glad/glad.h"

#define MUZZLE_NULL (void*)(1);

#ifdef MUZZLE_DANGEROUS_USE_MODERN_GRAPHICS_PIPELINE
    #include "../deps/glad/include/glad/glad.h"
#endif

#ifdef _WIN32
    // Include WinAPI if on windows. Required for MultiByteToWideChar
    #include "windows.h"
#endif

#ifdef __cplusplus
    #define MZ_LITERAL(x) x
#else
    #define MZ_LITERAL(x) (x)
#endif

typedef GLFWwindow* MUZZLE_WINDOW;
