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

	struct
	{
		GLuint fbos[2];
		GLuint textures[2];
		GLuint depth_buffers[2];
		GLuint depth_buffers_type; // 0 for Renderbuffer 1 for Texture
		GLuint vao;
		GLuint vbo;
	} framebuffer;

	GLFWwindow* window;
	FT_Library font_library;
	double delta_time;
	GLuint shader_passes[MUZZLE_MAX_SHADER_PASSES];
	size_t shader_passes_len;
	GLint render_order;
	GLint texture_units;
	int width;
	int height;
} mz_applet;

typedef enum mz_applet_flags
{
	APPLET_FLAG_RESIZBALE			= 1 << 0,
	APPLET_FLAG_VSYNC				= 1 << 1,
	APPLET_FLAG_TRACK_DELTA_TIME	= 1 << 2,
	APPLET_FLAG_ENABLE_SHADER_PASS_DEPTH_TEXTURE = 1 << 3
} mz_applet_flags;

typedef void (*mz_applet_main_dispatch_fn)(mz_applet*);

MZ_API mz_applet mz_initialize_applet(const char* window_title, int width, int height, mz_applet_flags flags);
MZ_API void mz_start_applet(mz_applet* applet, mz_applet_main_dispatch_fn main_dispatch);
MZ_API mz_boolean mz_keep_applet(mz_applet* applet);
MZ_API void mz_terminate_applet(mz_applet* applet);
MZ_API void mz_update_window_title(mz_applet* applet, const char* title);

#endif // MUZZLE_CORE_APPLET_H
