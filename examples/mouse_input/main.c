#include "input/mouse.h"
#include <Muzzle.h>
#include <stdint.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define PLAYER_SPEED 300
#define COLOR_SCHEME_LEN 5

typedef struct color_scheme
{
	mz_tint background;
	mz_tint foreground;
} color_scheme;

#define COLOR_SCHEME(a,b) (color_scheme){a,b}

void increment_current_scheme(uint8_t* ptr)
{
	if (++(*ptr) >= COLOR_SCHEME_LEN)
	{
		*ptr = 0;
	}
}

void applet_loop(mz_applet* applet)
{
	printf("Press left mouse button to go to next color scheme\nPress right mouse button to go to previous color scheme\n");
	
	mz_rectangle player = (mz_rectangle){0, 0, 100, 100};
	color_scheme color_schemes[COLOR_SCHEME_LEN] =
	{
		COLOR_SCHEME(TINT_MIDNIGHT_BLUE, TINT_BLUE),
		COLOR_SCHEME(TINT_WHITE, TINT_BLACK),
		COLOR_SCHEME(TINT_RED, TINT_YELLOW),
		COLOR_SCHEME(TINT_USAF_BLUE, TINT_GREEN),
		COLOR_SCHEME(TINT_MAGENTA, TINT_PINK)
	};

	uint8_t current_scheme = 0;
	mz_boolean mouse_down = MUZZLE_FALSE;
	mz_boolean mouse_up = MUZZLE_FALSE;

	while (mz_keep_applet(applet))
	{
		if (mz_mouse_pressed(applet, MOUSE_BUTTON_LEFT) && !mouse_down)
		{
			mouse_down = MUZZLE_TRUE;
			if (++current_scheme >= COLOR_SCHEME_LEN) current_scheme = 0;
		}

		if (mz_mouse_released(applet, MOUSE_BUTTON_LEFT) && mouse_down)
		{
			mouse_down = MUZZLE_FALSE;
		}

		if (mz_mouse_pressed(applet, MOUSE_BUTTON_RIGHT) && !mouse_up)
		{
			mouse_up = MUZZLE_TRUE;
			current_scheme = (current_scheme == 0) ? COLOR_SCHEME_LEN - 1 : current_scheme - 1;
		}

		if (mz_mouse_released(applet, MOUSE_BUTTON_RIGHT) && mouse_up)
		{
			mouse_up = MUZZLE_FALSE;
		}

		player.x = mz_get_mouse_xf(applet) - 50;
		player.y = mz_get_mouse_yf(applet) - 50;

		mz_begin_drawing(applet);
			mz_clear_screen(color_schemes[current_scheme].background);
			mz_draw_rectangle_type(applet, player, color_schemes[current_scheme].foreground);
		mz_end_drawing(applet);
	}
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [INPUT] - Mouse Input", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_VSYNC);
	mz_start_applet(&applet, applet_loop);

	mz_terminate_applet(&applet);
	return 0;
}
