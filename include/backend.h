#ifndef MUZZLE_BACKEND_H
#define MUZZLE_BACKEND_H

#if defined(__EMSCRIPTEN__)
	#define GLFW_INCLUDE_ES2
#endif

#ifndef MUZZLE_STRING_FMT_BUFFER_SIZE
	#define MUZZLE_STRING_FMT_BUFFER_SIZE 1024
#endif

#ifdef MUZZLE_EXCLUDE_STDLIB
	#define MZ_MEMORY_EXCLUDE_STDLIB
#endif

#include "core/Memory.h"

#define MUZZLE_FALSE (0)
#define MUZZLE_TRUE (1)
typedef unsigned char mz_boolean;

#define GLAD_GL_IMPLEMENTION
#include "../deps/glad/include/glad/glad.h"

#ifdef MUZZLE_USE_GLOBAL_DEPS
	#include <GLFW/glfw3.h>
#else
	#include "../deps/glfw/include/GLFW/glfw3.h"
#endif

#ifndef MUZZLE_NO_ASSERTIONS
	#define MZ_ASSERT(condition, details) do \
	{ \
	if ((condition) == 0) \
	{\
	fprintf(stderr, "Assertion '%s' failed in function '%s', details: %s", #condition, __func__, details); \
	exit(-1); \
	} } while (0)
#else
	#define MZ_ASSERT(condition, details) // Removes assertion from compiled code for optimization
#endif

#ifdef _WIN32
	// Required for MultiBytesToWideChar
	#define WIN32_LEAN_AND_MEAN
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

#ifdef __cplusplus
	#define MZ_LITERAL(x) x
#else
	#define MZ_LITERAL(x) (x)
#endif

#ifndef MUZZLE_DEFAULT_EXIT_KEY
	#define MUZZLE_DEFAULT_EXIT_KEY GLFW_KEY_ESCAPE
#endif

typedef GLFWwindow* mz_window;

#endif //MUZZLE_BACKEND_H