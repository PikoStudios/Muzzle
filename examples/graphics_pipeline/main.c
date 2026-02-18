/***
Graphics Pipelines were added for the purpose to make Muzzle far more flexible than ever. To showcase this, this example will demonstrate a basic 3D renderer
built with the use of the Graphics Pipeline API
*/

#include "core/pipeline.h"
#include "core/shader.h"
#include "primitives/sprite.h"
#include <Muzzle.h>
#include <stdio.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define ARRLEN(arr) (sizeof(arr) / sizeof(arr[0]))

void applet_loop(mz_applet* applet)
{
	mz_shader shader = mz_load_shader("../vert.glsl", "../frag.glsl");
	
	mz_vertex_attribute_descriptor attributes[] =
	{
		/* vec3 position */
		(mz_vertex_attribute_descriptor)
		{
			.size = 3,
			.type = VERTEX_ATTRIBUTE_TYPE_FLOAT
		},

		/* vec4 color */
		(mz_vertex_attribute_descriptor)
		{
			.size = 4,
			.type = VERTEX_ATTRIBUTE_TYPE_FLOAT
		}
	};

	// Creates the vertex buffer object, but does **NOT** allocate any memory for it
	mz_vertex_buffer vertex_buffer = mz_create_vertex_buffer(VERTEX_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, attributes, ARRLEN(attributes));

	float vertex_data[] =
	{
		/* vec3 position */   /* vec4 color */
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,

         0.5f,  0.5f,  0.5f,  0.0f, 0.5f, 0.5f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.5f, 0.5f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.5f, 0.5f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.5f, 0.5f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.5f, 0.5f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.5f, 0.5f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.5f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.5f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.5f, 1.0f
	};
	
	mz_allocate_vertex_buffer(&vertex_buffer, vertex_data, sizeof(vertex_data));

	mz_sprite_format color_attachment_formats[] = {SPRITE_FORMAT_RGBA8};

	mz_graphics_pipeline_descriptor pipeline_descriptor = (mz_graphics_pipeline_descriptor)
	{
		.shader = &shader,

		.framebuffer_width = applet->width,
		.framebuffer_height = applet->height,

		.color_attachment_count = ARRLEN(color_attachment_formats),
		.color_attachment_formats = color_attachment_formats,
		
		.create_depth_buffer = MUZZLE_TRUE,
		.depth_buffer_type = DEPTH_BUFFER_TYPE_RENDERBUFFER,
	};

	mz_graphics_pipeline pipeline = mz_create_graphics_pipeline(&pipeline_descriptor);

	mz_sprite color_attachment = mz_get_graphics_pipeline_color_attachment_texture(&pipeline, 0);

	float time = 0.0f;

	mz_upload_uniform_vec2(shader, "uScreenResolution", (mz_vec2){applet->width, applet->height});
	mz_upload_uniform_float(shader, "uCameraFov", 90.f);
	
	while (mz_keep_applet(applet))
	{
		time += applet->delta_time;
		mz_upload_uniform_float(shader, "uTime", time);
		
		mz_begin_drawing(applet);
			mz_clear_screen(TINT_GRAY);
			
			mz_clear_graphics_pipeline_color_attachments(&pipeline, (mz_tint){0, 0, 0, 0});
			mz_clear_graphics_pipeline_depth_buffer(&pipeline, 1.0f);
			
			mz_dispatch_graphics_pipeline(&pipeline, &vertex_buffer, 0, 36);
			mz_draw_sprite(applet, &color_attachment, 0, 0, TINT_WHITE);
		mz_end_drawing(applet);
	}

	mz_unload_shader(shader);
	mz_unload_vertex_buffer(&vertex_buffer);
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [CORE] - Graphics Pipeline", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_RESIZBALE | APPLET_FLAG_TRACK_DELTA_TIME | APPLET_FLAG_VSYNC);
	mz_start_applet(&applet, applet_loop);
	
	mz_terminate_applet(&applet);
	return 0;
}
