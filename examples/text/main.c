#include "core/drawing.h"
#include "core/font.h"
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define ASSETS_DIR "../asset/"

void applet_loop(mz_applet* applet)
{
	mz_font font = mz_load_font(applet, ASSETS_DIR "OpenSans-Regular.ttf");

	if (font.glyph_count > 0)
	{
		printf("Loaded font!\n");
	}
	
	while (mz_keep_applet(applet))
	{
#ifndef EXCLUDE_FRAMETIME
		printf("FPS: %f (%f ms)\r", 1/applet->delta_time, applet->delta_time * 1000);
		fflush(stdout);
#endif

		mz_begin_drawing(applet);
			mz_clear_screen(TINT_GRAY);
			mz_draw_text(applet, "Hello World from Muzzle!", 250.f, 250.f,48.f, &font, TINT_BLACK);
		mz_end_drawing(applet);
	}

	mz_unload_font(&font);
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [PRIMITIVE/CORE] - Text/Fonts", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_RESIZBALE | APPLET_FLAG_TRACK_DELTA_TIME);
	mz_start_applet(&applet, applet_loop);
	
	mz_terminate_applet(&applet);
	return 0;
}
