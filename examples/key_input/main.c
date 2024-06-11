#include "core/drawing.h"
#include <Muzzle.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define PLAYER_SPEED 300

void applet_loop(mz_applet* applet)
{
	mz_rectangle player = (mz_rectangle){(float)(SCREEN_WIDTH)/2 - 50, (float)(SCREEN_HEIGHT)/2 - 50, 100, 100};

	while (mz_keep_applet(applet))
	{
		if (mz_key_pressed(applet, KEY_D))
		{
			player.x += PLAYER_SPEED * applet->delta_time;
		}

		else if (mz_key_pressed(applet, KEY_A))
		{
			player.x -= PLAYER_SPEED * applet->delta_time;
		}

		if (mz_key_pressed(applet, KEY_S))
		{
			player.y += PLAYER_SPEED * applet->delta_time;
		}

		else if (mz_key_pressed(applet, KEY_W))
		{
			player.y -= PLAYER_SPEED * applet->delta_time;
		}

		mz_begin_drawing(applet);
			mz_clear_screen(TINT_MIDNIGHT_BLUE);
			mz_draw_rectangle_type(applet, player, TINT_BLUE);
		mz_end_drawing(applet);
	}
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [INPUT] - Key Input", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_VSYNC | APPLET_FLAG_TRACK_DELTA_TIME);
	mz_start_applet(&applet, applet_loop);

	mz_terminate_applet(&applet);
	return 0;
}
