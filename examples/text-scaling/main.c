#include <Muzzle.h>
#include <stdio.h>
#include <math.h>
#define EXCLUDE_FRAMETIME
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define ASSETS_DIR "../asset/"

void applet_loop(mz_applet* applet)
{
	mz_font font = mz_load_font(applet, ASSETS_DIR "OpenSans-Regular.ttf");

	if (font.glyph_count > 0)
	{
		mz_log_status(LOG_STATUS_SUCCESS, "Loaded font!");
	}

	double elapsed = 0;
	float size = 0;

	while (mz_keep_applet(applet))
	{
		elapsed += applet->delta_time;
		size = 128.f * sin(elapsed);
		
		mz_begin_drawing(applet);
			mz_clear_screen(TINT_GRAY);
			mz_draw_text(applet, "Lorem Ipsum", SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, size, &font, TINT_BLACK);
		mz_end_drawing(applet);
	}

	mz_unload_font(&font);
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [PRIMITIVE/CORE] - Text Scaling", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_RESIZBALE | APPLET_FLAG_TRACK_DELTA_TIME);
	mz_start_applet(&applet, applet_loop);
	
	mz_terminate_applet(&applet);
	return 0;
}
