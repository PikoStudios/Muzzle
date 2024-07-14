#include "core/applet.h"
#include "core/tint.h"
#include "primitives/circle.h"
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void applet_loop(mz_applet* applet)
{
	float x = 0;
	float y = 0;
	
	while (mz_keep_applet(applet))
	{
		mz_begin_drawing(applet);
			mz_clear_screen(TINT_GRAY);
			mz_draw_circle(applet, SCREEN_WIDTH / 2 + x, SCREEN_HEIGHT / 2 + y, 20.f, TINT_ORANGE);
			mz_draw_circle(applet, SCREEN_WIDTH / 2 + 30, SCREEN_HEIGHT / 2 - 30, 32.f, TINT_BLUE);
		mz_end_drawing(applet);

		x += 0.05;
		y -= 0.05;
	}
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [PRIMITIVES] - Circle", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_VSYNC | APPLET_FLAG_RESIZBALE);
	mz_start_applet(&applet, applet_loop);

	mz_terminate_applet(&applet);
	return 0;
}
