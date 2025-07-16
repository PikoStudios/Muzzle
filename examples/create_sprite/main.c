#include "core/applet.h"
#include "core/drawing.h"
#include "core/tint.h"
#include "primitives/sprite.h"
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void applet_loop(mz_applet* applet)
{
	unsigned char* pixels = MZ_CALLOC(sizeof(unsigned char), SCREEN_WIDTH * SCREEN_HEIGHT * 4);

	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
	{
		float x = i % SCREEN_WIDTH;
		float y = i / SCREEN_WIDTH;

		int idx = i * 4;

		pixels[idx + 0] = (x / SCREEN_WIDTH) * 255; // Red
		pixels[idx + 1] = (y / SCREEN_HEIGHT) * 255; // Green
		pixels[idx + 2] = 127; // Blue
		pixels[idx + 3] = 255; // Alpha
	}
	
	mz_sprite sprite = mz_create_sprite(SCREEN_WIDTH, SCREEN_HEIGHT, SPRITE_WRAPPING_MODE_REPEAT, SPRITE_FILTER_MODE_NEAREST, SPRITE_FILTER_MODE_LINEAR, SPRITE_FORMAT_RGBA8, pixels);
	MZ_FREE(pixels);
	
	while (mz_keep_applet(applet))
	{
		mz_begin_drawing(applet);
			mz_clear_screen(TINT_GRAY);
			mz_draw_sprite(applet, &sprite, 0, 0, TINT_WHITE);
		mz_end_drawing(applet);
	}

	mz_unload_sprite(&sprite);
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [CORE] - Sprite Creation", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_VSYNC);
	mz_start_applet(&applet, applet_loop);
	
	mz_terminate_applet(&applet);
	return 0;
}
