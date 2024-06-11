#ifndef MUZZLE_CORE_APPLET_H
#define MUZZLE_CORE_APPLET_H

#include "backend.h"
#include "core/quad_renderer.h"

typedef struct mz_applet
{
	GLFWwindow* window;
	int width;
	int height;
	GLint render_order;
	struct mz_quad_renderer quad_renderer;
	double delta_time;
	mz_boolean delta_time_flag;
} mz_applet;

typedef enum mz_applet_flags
{
	APPLET_FLAG_RESIZBALE			= 1 << 0,
	APPLET_FLAG_VSYNC				= 1 << 1,
	APPLET_FLAG_TRACK_DELTA_TIME	= 1 << 2,
} mz_applet_flags;

typedef void (*mz_applet_main_dispatch_fn)(mz_applet*);

MZ_API mz_applet mz_initialize_applet(const char* window_title, int width, int height, mz_applet_flags flags);
MZ_API void mz_start_applet(mz_applet* applet, mz_applet_main_dispatch_fn main_dispatch);
MZ_API mz_boolean mz_keep_applet(mz_applet* applet);
MZ_API void mz_terminate_applet(mz_applet* applet);

#endif // MUZZLE_CORE_APPLET_H
