#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1
#define SCREEN_HEIGHT 1
#define ASSETS_DIR "../asset/"

void applet_loop(mz_applet* applet)
{
	for (int i = 0; i < 100; i++)
	{
		mz_font font = mz_load_font(applet, ASSETS_DIR "OpenSans-Regular.ttf");

		if (font.glyph_count > 0)
		{
			printf("Test attempt #%d passed with %d glyphs loaded\n", i + 1, font.glyph_count);
		}

		else
		{
			printf("Test attempt #%d failed\n", i + 1);
		}

		mz_unload_font(&font);
	}
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [PRIMITIVE/CORE] - Font Stress Test", 1, 1, APPLET_FLAG_RESIZBALE | APPLET_FLAG_TRACK_DELTA_TIME);
	mz_start_applet(&applet, applet_loop);
	
	mz_terminate_applet(&applet);
	return 0;
}
