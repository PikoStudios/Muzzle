#include "core/applet.h"
#include "core/tint.h"
#include "primitives/sprite.h"
#include <Muzzle.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// ../ because the executable will be in a build folder
#ifndef ASSETS_DIR
	#define ASSETS_DIR "../"
#endif

void applet_loop(mz_applet* applet)
{
	mz_sprite muzzle_logo = mz_load_sprite(ASSETS_DIR "muzzle_logo.png");
	mz_sprite rotation_logo = mz_load_sprite(ASSETS_DIR "rotation.png");

	double elapsed = 0.0f;

	while (mz_keep_applet(applet))
	{
		mz_tint tint = (mz_tint){abs((int)(cos(elapsed / 2) * 255)), abs((int)(sin(elapsed / 2) * 255)), 255, 255};

		elapsed += applet->delta_time * 8;

		mz_begin_drawing(applet);
			mz_clear_screen(TINT_PURPLE);

			mz_draw_sprite(applet, &muzzle_logo, (SCREEN_WIDTH - muzzle_logo.width) * 0.5, (SCREEN_HEIGHT - muzzle_logo.height) * 0.5, TINT_WHITE);
			mz_draw_sprite_rotated(applet, &muzzle_logo, (SCREEN_WIDTH - muzzle_logo.width) * 0.5, (SCREEN_HEIGHT - muzzle_logo.height) * 0.5 + 250, elapsed, TINT_WHITE);
			mz_draw_sprite_rotated(applet, &rotation_logo, 100, 100, elapsed, TINT_WHITE);
			mz_draw_sprite_flipped(applet, &muzzle_logo, 300, 150, SPRITE_FLIP_ORIENTATION_HORIZONTAL, tint);
			mz_draw_sprite_flipped(applet, &muzzle_logo, 700, 150, SPRITE_FLIP_ORIENTATION_VERTICAL, tint);

		mz_end_drawing(applet);
	}

	mz_unload_sprite(&muzzle_logo);
	mz_unload_sprite(&rotation_logo);
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [PRIMITIVES] - Sprites", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_RESIZBALE | APPLET_FLAG_TRACK_DELTA_TIME);
	mz_start_applet(&applet, applet_loop);

	mz_terminate_applet(&applet);
	return 0;
}
