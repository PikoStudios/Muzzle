#ifndef MUZZLE_CORE_APPLET_H
#define MUZZLE_CORE_APPLET_H

#include "backend.h"
#include "core/circle_renderer.h"
#include "core/quad_renderer.h"
#include "core/sprite_renderer.h"
#include "core/text_renderer.h"

typedef struct mz_applet
{
	struct mz_quad_renderer quad_renderer;
	struct mz_sprite_renderer sprite_renderer;
	struct mz_circle_renderer circle_renderer;
	struct mz_text_renderer text_renderer;

	double delta_time;
	GLint render_order;
	GLint texture_units;
	int width;
	int height;
	
	struct
	{
		GLuint fbos[2];
		GLuint textures[2];
		GLuint depth_buffers[2];
		GLuint vao;
		GLuint vbo;
		GLuint depth_buffers_type:1; // 0 for Renderbuffer 1 for Texture
		mz_boolean dirty:1;
	} framebuffer;
	
	GLFWwindow* window;
	GLuint shader_passes[MUZZLE_MAX_SHADER_PASSES];
	size_t shader_passes_len;

	FT_Library font_library;
} mz_applet;

typedef enum mz_applet_flags
{
	APPLET_FLAG_RESIZBALE							= 1 << 0,
	APPLET_FLAG_VSYNC								= 1 << 1,
	APPLET_FLAG_TRACK_DELTA_TIME					= 1 << 2,
	APPLET_FLAG_ENABLE_SHADER_PASS_DEPTH_TEXTURE	= 1 << 3,
	APPLET_FLAG_FULLSCREEN 							= 1 << 4
} mz_applet_flags;

typedef GLFWscrollfun mz_mouse_scroll_callback_fn;
typedef GLFWcursorposfun mz_mouse_position_callback_fn;
typedef GLFWcursorenterfun mz_mouse_crossed_window_boundary_callback_fn;
typedef GLFWmousebuttonfun mz_mouse_button_input_callback_fn;

typedef GLFWkeyfun mz_key_input_callback_fn;
typedef GLFWcharfun mz_character_input_callback_fn;

typedef GLFWdropfun mz_file_dropped_callback_fn;

typedef GLFWwindowposfun mz_window_position_callback_fn;
typedef GLFWwindowsizefun mz_window_size_changed_callback_fn;
typedef GLFWwindowfocusfun mz_window_focus_changed_callback_fn;
typedef GLFWwindowiconifyfun mz_window_min_maximized_callback_fn;

typedef enum mz_callback_type
{
	CALLBACK_MOUSE_SCROLL = 0,
	CALLBACK_MOUSE_POSITION,
	CALLBACK_MOUSE_CROSSED_WINDOW_BOUNDARY,
	CALLBACK_MOUSE_BUTTON_INPUT,
	
	CALLBACK_KEY_INPUT,
	CALLBACK_CHARACTER_INPUT,
	
	CALLBACK_FILE_DROPPED,

	CALLBACK_WINDOW_POSITION,
	CALLBACK_WINDOW_SIZE_CHANGED,
	CALLBACK_WINDOW_FOCUS_CHANGED,
	CALLBACK_WINDOW_MIN_MAXIMIZED
} mz_callback_type;

typedef union mz_callback
{
	mz_mouse_scroll_callback_fn mouse_scroll;
	mz_mouse_position_callback_fn mouse_position;
	mz_mouse_crossed_window_boundary_callback_fn mouse_crossed_window_boundary;
	mz_mouse_button_input_callback_fn mouse_button_input;
	
	mz_key_input_callback_fn key_input;
	mz_character_input_callback_fn character_input;
	
	mz_file_dropped_callback_fn file_dropped;

	mz_window_position_callback_fn window_position;
	mz_window_size_changed_callback_fn window_size_changed;
	mz_window_focus_changed_callback_fn window_focus_changed;
	mz_window_min_maximized_callback_fn window_min_maximized;
} mz_callback;

typedef void (*mz_applet_main_dispatch_fn)(mz_applet*);

MZ_API mz_applet mz_initialize_applet(const char* window_title, int width, int height, mz_applet_flags flags);
MZ_API void mz_start_applet(mz_applet* applet, mz_applet_main_dispatch_fn main_dispatch);
MZ_API mz_boolean mz_keep_applet(mz_applet* applet);
MZ_API void mz_terminate_applet(mz_applet* applet);
MZ_API void mz_update_window_title(mz_applet* applet, const char* title);

MZ_API void mz_set_callback(mz_applet* applet, mz_callback_type type, mz_callback callback);

#endif // MUZZLE_CORE_APPLET_H
