#include "core/applet.h"
#include "core/drawing.h"
#include "core/tint.h"
#include "primitives/rectangle.h"
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 800
#define CELL_SIZE 40
#define EXCLUDE_FRAMETIME

void print_fps(mz_applet* applet)
{
#ifndef EXCLUDE_FRAMETIME
	printf("FPS: %f (%f ms)\r", 1/applet->delta_time, applet->delta_time * 1000);
	fflush(stdout);
#endif
}

void draw_grid(mz_applet* applet)
{
	for (int y = 0; y < SCREEN_HEIGHT; y += CELL_SIZE)
	{
		mz_draw_rectangle(applet, 0, y, SCREEN_WIDTH, 1, TINT_GRAY);
	}

	for (int x = 0; x < SCREEN_WIDTH; x += CELL_SIZE)
	{
		mz_draw_rectangle(applet, x, 0, 1, SCREEN_HEIGHT, TINT_GRAY);
	}
}

void applet_loop(mz_applet* applet)
{
	while (mz_keep_applet(applet))
	{
		print_fps(applet);

		mz_begin_drawing(applet);
			mz_clear_screen(TINT_BLACK);
			draw_grid(applet);
		mz_end_drawing(applet);
	}
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [EXAMPLE] - Tetris", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_VSYNC | APPLET_FLAG_TRACK_DELTA_TIME);
	mz_start_applet(&applet, applet_loop);
	
	mz_terminate_applet(&applet);
	return 0;
}
