#include "core/drawing.h"
#include <stdio.h>
#include "backend.h"
#include "core/circle_renderer.h"
#include "core/quad_renderer.h"
#include "core/sprite_renderer.h"
#define ONE_OVER_255 0.0039215686

void mz_begin_drawing(mz_applet* applet)
{
	MZ_TRACK_FUNCTION();
	glfwSwapBuffers(applet->window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Offscreen framebuffer used, so clear it
	if (applet->shader_passes_len > 0)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, applet->framebuffer_buffers[0]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		applet->shader_passes_len = 0;
	}
}

void mz_end_drawing(mz_applet* applet)
{
	MZ_TRACK_FUNCTION();

	if (applet->quad_renderer.quad_count > 0)
	{
		mz_quad_renderer_flush(&applet->quad_renderer, applet->width, applet->height);
	}

	if (applet->sprite_renderer.sprite_count > 0)
	{
		mz_sprite_renderer_flush(&applet->sprite_renderer, applet->width, applet->height);
	}

	if (applet->circle_renderer.circle_count > 0)
	{
		mz_circle_renderer_flush(&applet->circle_renderer, applet->width, applet->height);
	}

	if (applet->shader_passes_len > 0)
	{
		MZ_TRACK_FUNCTION_STAGE("mz_end_drawing shader passes");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, applet->framebuffer_buffers[1]);

		for (int i = 0; i < applet->shader_passes_len; i++)
		{
			glUseProgram(applet->shader_passes[i]);
			// TODO: Render quad for shader pass
		}

		MZ_TRACK_FUNCTION();
	}
	applet->render_order = 0;

	glfwPollEvents();
}

void mz_clear_screen(mz_tint tint)
{
	MZ_TRACK_FUNCTION();

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
