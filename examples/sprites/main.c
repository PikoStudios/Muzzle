#include "core/tint.h"
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// ../ because the executable will be in a build folder
#ifndef ASSETS_DIR
	#define ASSETS_DIR "../"
#endif

void applet_loop(mz_applet* applet)
{
	mz_sprite muzzle_logo = mz_load_sprite(ASSETS_DIR "muzzle_logo.png");
	
	while (mz_keep_applet(applet))
	{
		mz_begin_drawing(applet);
			mz_clear_screen(TINT_PURPLE);
			mz_draw_sprite(applet, &muzzle_logo, (SCREEN_WIDTH - muzzle_logo.width) * 0.5, (SCREEN_HEIGHT - muzzle_logo.height) * 0.5, TINT_WHITE);
		mz_end_drawing(applet);
	}

	mz_unload_sprite(&muzzle_logo);
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [PRIMITIVES] - Sprites", SCREEN_WIDTH, SCREEN_HEIGHT,APPLET_FLAG_RESIZBALE);
	mz_start_applet(&applet, applet_loop);

	mz_terminate_applet(&applet);
	return 0;
}
