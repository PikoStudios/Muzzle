#include "core/applet.h"
#include "core/drawing.h"
#include "core/tint.h"
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void applet_loop(mz_applet* applet)
{
	while (mz_keep_applet(applet))
	{
#ifndef EXCLUDE_FRAMETIME
		printf("FPS: %f (%f ms)\r", 1/applet->delta_time, applet->delta_time * 1000);
		fflush(stdout);
#endif
		mz_begin_drawing(applet);
			mz_clear_screen(TINT_GRAY);
		mz_end_drawing(applet);
	}
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [CORE] - Blank Window", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_RESIZBALE | APPLET_FLAG_TRACK_DELTA_TIME);
	mz_start_applet(&applet, applet_loop);
	
	mz_terminate_applet(&applet);
	return 0;
}
