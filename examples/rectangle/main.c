#include "core/applet.h"
#include "core/tint.h"
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void applet_loop(mz_applet* applet)
{
	while (mz_keep_applet(applet))
	{
		mz_begin_drawing(applet);
			mz_clear_screen(TINT_GRAY);
			mz_draw_rectangle(applet, 330.f, 300.f, 50.f, 50.f, TINT_MAGENTA);
			mz_draw_rectangle(applet, 300.f, 300.f, 50.f, 50.f, TINT_BLUE);
			mz_draw_rectangle(applet, 0.f, 0.f, 150.f, 150.f, TINT_YELLOW);
			mz_draw_rectangle(applet, SCREEN_WIDTH - 300.f, SCREEN_HEIGHT - 400.f, 200.f, 350.f, TINT_ORANGE);
		mz_end_drawing(applet);
	}
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [PRIMITIVES] - Rectangle", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_VSYNC | APPLET_FLAG_RESIZBALE);
	mz_start_applet(&applet, applet_loop);

	mz_terminate_applet(&applet);
	return 0;
}
