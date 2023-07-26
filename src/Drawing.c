#include "core/Drawing.h"

void begin_drawing(Applet* applet)
{
	// TODO: Find really weird memory glitch where clearing the screen causes
	// active_batch->quad_count = clear_color.b?????
	static int frame = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	begin_batch(applet->active_batch);
	printf("Frame %d (Check 1): quad_count = %d\n", ++frame, applet->active_batch->quad_count);
}

void end_drawing(Applet* applet)
{
	static int frame = 1;
	
	glfwSwapBuffers(applet->window_handle);
	glfwPollEvents();
	printf("Frame %d (Check 2): quad_count = %d\n", frame, applet->active_batch->quad_count);
	end_batch(applet->active_batch);
	printf("Frame %d (Check 3): quad_count = %d\n", frame++, applet->active_batch->quad_count);
	glFlush();
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