#include "core/drawing.h"
#include "core/circle_renderer.h"
#include "core/quad_renderer.h"
#include "core/sprite_renderer.h"
#define ONE_OVER_255 0.0039215686

void mz_begin_drawing(mz_applet* applet)
{
	glfwSwapBuffers(applet->window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void mz_end_drawing(mz_applet* applet)
{
	if (applet->quad_renderer.quad_count > 0)
	{
		mz_quad_renderer_flush(&applet->quad_renderer, applet->width, applet->height, applet->render_order);
	}

	if (applet->sprite_renderer.sprite_count > 0)
	{
		mz_sprite_renderer_flush(&applet->sprite_renderer, applet->width, applet->height, applet->render_order);
	}

	if (applet->circle_renderer.circle_count > 0)
	{
		mz_circle_renderer_flush(&applet->circle_renderer, applet->width, applet->height, applet->render_order);
	}

	applet->render_order = 0;

	glFlush(); // TODO: needed?
	glfwPollEvents();
}

void mz_clear_screen(mz_tint tint)
{
#ifndef MUZZLE_PREFER_MULTIPLICATION
	glClearColor(
		(float)(tint.r) / 255,
		(float)(tint.g) / 255,
		(float)(tint.b) / 255,
		(float)(tint.a) / 255
	);
#else
#warning "Multiplication over division may cause small imperfects due to size of constant"
	glClearColor(
		(float)(tint.r) * ONE_OVER_255,
		(float)(tint.g) * ONE_OVER_255,
		(float)(tint.b) * ONE_OVER_255,
		(float)(tint.a) * ONE_OVER_255
	);
#endif
}
