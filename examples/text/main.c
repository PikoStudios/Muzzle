#include "lorem_ipsum.h"
#include <Muzzle.h>
#include <stdio.h>
#define EXCLUDE_FRAMETIME
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define ASSETS_DIR "../asset/"

void varity_scene(mz_applet* applet, mz_font* font)
{
	mz_draw_rectangle(applet, 0.f, 48.f, 50.f, 50.f, TINT_ORANGE);
	mz_draw_text(applet, "The quick brown fox jumps over the lazy dog", 0.f, 48.f, 48.f, font, TINT_BLACK);
	mz_draw_text(applet, "abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+-=1234567890`~[]:;\"',<.>/?", 20.f, 200.f, 38.f, font, TINT_BLACK);
	mz_draw_text(applet, "Hello World from Muzzle!\nHello World from PikoStudios!!", 250.f, 250.f,48.f, font, TINT_BLUE);
}

void lorem_ipsum_scene(mz_applet* applet, mz_font* font)
{
	mz_draw_text(applet, LOREM_IPSUM, 0.f, 48.f, 48.f, font, TINT_BLACK);
}

void applet_loop(mz_applet* applet)
{
	mz_font font = mz_load_font(applet, ASSETS_DIR "OpenSans-Regular.ttf");

	if (font.glyph_count > 0)
	{
		mz_log_status(LOG_STATUS_SUCCESS, "Loaded font!");
	}

	char scene;

#ifndef FORCE_SCENE
	do
	{
		fflush(stdin);
		printf("Select a scene: (0) Varity, (1) Lorem Ipsum\n");
		scene = getchar();
	} while (scene != '0' && scene != '1');
#else
	scene = FORCE_SCENE;
#endif

	while (mz_keep_applet(applet))
	{
#ifndef EXCLUDE_FRAMETIME
		printf("FPS: %f (%f ms)\r", 1/applet->delta_time, applet->delta_time * 1000);
		fflush(stdout);
#endif

		mz_begin_drawing(applet);
			mz_clear_screen(TINT_GRAY);

			switch (scene)
			{
				case '0':
					varity_scene(applet, &font);
					break;

				case '1':
					lorem_ipsum_scene(applet, &font);
					break;

				default:
					break;		
			}
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
