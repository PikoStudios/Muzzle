#ifndef MUZZLE_BACKEND_H
#define MUZZLE_BACKEND_H

#include <stdint.h>

#include "core/memory.h"

#ifdef __EMSCRIPTEN__
	#define GLFW_INCLUDE_ES2
#endif

typedef uint8_t mz_boolean;
#define MZ_BOOLEAN_CAST(x) (((x)) ? 1 : 0)

#define MUZZLE_FALSE 0
#define MUZZLE_TRUE 1

#ifndef MUZZLE_GLAD_INCLUDE_PATH
	#define MUZZLE_GLAD_INCLUDE_PATH "../deps/glad/include/glad/glad.h"
#endif

#define GLAD_GL_IMPLEMENTION
#include MUZZLE_GLAD_INCLUDE_PATH

#ifndef MUZZLE_GLFW_INCLUDE_PATH
	#define MUZZLE_GLFW_INCLUDE_PATH "../deps/glfw/include/GLFW/glfw3.h"
#endif

#include MUZZLE_GLFW_INCLUDE_PATH

#ifndef MUZZLE_FREETYPE_FT2BUILD_INCLUDE_PATH
	#define MUZZLE_FREETYPE_FT2BUILD_INCLUDE_PATH "../deps/freetype/include/ft2build.h"
#endif

#include MUZZLE_FREETYPE_FT2BUILD_INCLUDE_PATH
#include FT_FREETYPE_H

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>

	#ifdef BUILD_LIBYPE_SHARED
		#define MZ_API __declspec(dllexport)
	#else
		#ifdef USE_LIBTYPE_SHARED
			#define MZ_API __declspec(dllimport)
		#endif
	#endif
#endif

#ifndef MZ_API
	#define MZ_API
#endif

#ifndef __cplusplus
	#define MZ_LITERAL(x) (x)
#else
	#define MZ_LITERAL(x) x
#endif

#ifdef MUZZLE_DEBUG_BUILD
	extern char* __mz_debug_current_function_name;

	#ifdef _WIN32
		//#include <intrin.h>
		#define MZ_TRIGGER_BREAKPOINT() DebugBreak()
	#else
		#include <signal.h>
		#define MZ_TRIGGER_BREAKPOINT() raise(SIGTRAP)
	#endif
	
	#define MZ_ASSERT_DETAILED(expression, error_msg) if (!(expression)) { printf("\nAssertion " #expression " failed: " #error_msg "\n"); exit(-1); MZ_TRIGGER_BREAKPOINT(); }
	#define MZ_TRACK_FUNCTION() __mz_debug_current_function_name = (char*)__func__
	#define MZ_TRACK_FUNCTION_STAGE(s) __mz_debug_current_function_name = s
	#define MZ_GET_CURRENT_FUNCTION() __mz_debug_current_function_name
#else
	// No effect without MUZZLE_DEBUG_BUILD defined
	#define MZ_TRIGGER_BREAKPOINT()
	
	// No effect without MUZZLE_DEBUG_BUILD defined
	#define MZ_ASSERT_DETAILED(expression, error_msg)

	// No effect without MUZZLE_DEDBUG_BUILD defined
	#define MZ_TRACK_FUNCTION()
	
	// No effect without MUZZLE_DEDBUG_BUILD defined
	#define MZ_TRACK_FUNCTION_STAGE(s)
	
	// No effect without MUZZLE_DEDBUG_BUILD defined
	#define MZ_GET_CURRENT_FUNCTION() "debug features disabled"
#endif

#ifndef MUZZLE_EXIT_KEY
	#define MUZZLE_EXIT_KEY GLFW_KEY_ESCAPE
#endif

#ifndef MUZZLE_OPENGL_VERSION_MAJOR
	#define MUZZLE_OPENGL_VERSION_MAJOR 4
#endif

#ifndef MUZZLE_OPENGL_VERSION_MINOR
	#define MUZZLE_OPENGL_VERSION_MINOR 6
#endif

#if MUZZLE_OPENGL_VERSION_MAJOR < 4 || MUZZLE_OPENGL_VERSION_MINOR < 5
	#warning "OpenGL versions lower than 4.5 is not recommended. OpenGL versions less than 4.3 are NOT supported and will likely result in errors and versions less than 4.5 will have certain features limited. Read docs/less_than_4_5.md"
#endif

#ifndef MUZZLE_TEXT_SOURCE_FONT_SIZE
	#define MUZZLE_TEXT_SOURCE_FONT_SIZE 256
#endif

#ifndef MUZZLE_TEXT_DEFAULT_SPACE_WIDTH
	#define MUZZLE_TEXT_DEFAULT_SPACE_WIDTH 10
#endif

#ifndef MUZZLE_MAX_SHADER_PASSES
	#define MUZZLE_MAX_SHADER_PASSES 32
#endif

#ifndef MUZZLE_QUAD_BUFFER_CAPACITY
	#define MUZZLE_QUAD_BUFFER_CAPACITY 100
#endif

#ifndef MUZZLE_SPRITE_BUFFER_CAPACITY
	#define MUZZLE_SPRITE_BUFFER_CAPACITY 100
#endif

#ifndef MUZZLE_SPRITE_TEXTURE_BUFFER_CAPACITY
	#define MUZZLE_SPRITE_TEXTURE_BUFFER_CAPACITY 32
#endif

#ifndef MUZZLE_CIRCLE_BUFFER_CAPACITY
	#define MUZZLE_CIRCLE_BUFFER_CAPACITY 100
#endif

#ifndef MUZZLE_TEXT_BUFFER_CAPACITY
	#define MUZZLE_TEXT_BUFFER_CAPACITY 200
#endif

#endif // MUZZLE_BACKEND_H
