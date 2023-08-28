#include "core/Drawing.h"
#include "internal/globals.internal.h"

void begin_drawing(Applet* applet)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	begin_batch(applet->active_batch);

	mz_globals_internal_active_batch = applet->active_batch;
}

void end_drawing(Applet* applet)
{
	glfwSwapBuffers(applet->window_handle);
	glfwPollEvents();
	end_batch(applet->active_batch);
	glFlush();

	mz_globals_internal_active_batch = applet->active_batch;
}

void clear_screen(tint color_drawn)
{
	glClearColor(
		(float)(color_drawn.r) / 255,
		(float)(color_drawn.g) / 255,
		(float)(color_drawn.b) / 255,
		(float)(color_drawn.a) / 255
	);
}

void begin_quad_shader(shader_program program, Applet* applet)
{
	end_batch(applet->active_batch);
	begin_batch(applet->active_batch);
	
	applet->active_batch->quad_shader_program = program;
}

void end_quad_shader(Applet* applet)
{
	end_batch(applet->active_batch);
	begin_batch(applet->active_batch);
	
	applet->active_batch->quad_shader_program = applet->active_batch->quad_fallback_shader_program;
}