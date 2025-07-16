#include "core/applet.h"
#include "core/drawing.h"
#include "core/shader.h"
#include "core/tint.h"
#include "primitives/sprite.h"
#include <Muzzle.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void applet_loop(mz_applet* applet)
{
	mz_sprite compute_texture = mz_create_sprite(SCREEN_WIDTH, SCREEN_HEIGHT, SPRITE_WRAPPING_MODE_REPEAT, SPRITE_FILTER_MODE_NEAREST, SPRITE_FILTER_MODE_NEAREST, SPRITE_FORMAT_RGBA32F, NULL);
	mz_compute_pipeline compute_pipeline = mz_create_compute_pipeline("../comp.glsl", MUZZLE_TRUE, &compute_texture, 0);

	mz_upload_uniform_vec2(compute_pipeline.shader, "uScreenResolution", (mz_vec2){SCREEN_WIDTH, SCREEN_HEIGHT});
	mz_dispatch_compute_pipeline(&compute_pipeline, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
	
	while (mz_keep_applet(applet))
	{
		mz_begin_drawing(applet);
			mz_clear_screen(TINT_GRAY);
			mz_draw_sprite(applet, &compute_texture, 0, 0, TINT_WHITE);
		mz_end_drawing(applet);
	}

	mz_unload_compute_pipeline(&compute_pipeline);
	mz_unload_sprite(&compute_texture);
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [CORE] - Compute Shader", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_VSYNC);
	mz_start_applet(&applet, applet_loop);
	
	mz_terminate_applet(&applet);
	return 0;
}
