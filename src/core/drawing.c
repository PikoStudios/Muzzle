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
		glBindFramebuffer(GL_FRAMEBUFFER, applet->framebuffer.fbos[0]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindFramebuffer(GL_FRAMEBUFFER, applet->framebuffer.fbos[1]);
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


		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(applet->framebuffer.vao);
		glBindBuffer(GL_ARRAY_BUFFER, applet->framebuffer.vbo);

		for (int i = 0; i < applet->shader_passes_len; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, i == applet->shader_passes_len - 1 ? 0 : applet->framebuffer.fbos[(i + 1) % 2]);

			glBindTexture(GL_TEXTURE_2D, applet->framebuffer.textures[i % 2]);

			glUseProgram(applet->shader_passes[i]);

			// Depth Buffer Texture
			if (applet->framebuffer.depth_buffers_type == 1)
			{
				GLuint depth_loc = glGetUniformLocation(applet->shader_passes[i], "uDepthTexture");
				
				if (depth_loc != -1)
				{
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, applet->framebuffer.depth_buffers[i % 2]);
					glActiveTexture(GL_TEXTURE0);
					
					glUniform1i(depth_loc, 1);
				}
			}

			GLuint texture_loc = glGetUniformLocation(applet->shader_passes[i], "uScreenTexture");
			GLuint resolution_loc = glGetUniformLocation(applet->shader_passes[i], "uScreenResolution");

			if (texture_loc != -1)
			{
				glUniform1i(texture_loc, 0);
			}

			if (resolution_loc != -1)
			{
				glUniform2f(resolution_loc, applet->width, applet->height);
			}

			glDrawArrays(GL_TRIANGLES, 0, 6);
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
