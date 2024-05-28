#include "core/applet.h"
#include <Muzzle.h>
#include <stdio.h>
#include <time.h>
#define RANDINT(min, max) (rand() % (max - min + 1)) + min
#define TINT_ADD(t1, t2) (mz_tint){t1.r + t2.r, t1.b + t2.b, t1.g + t2.g, t1.a}
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void randomize_modifier(mz_tint* modifier, mz_boolean positive)
{
	int random = positive ? RANDINT(1, 2) : RANDINT(-2, 1);
	
	modifier->r = random;
	modifier->g = random;
	modifier->b = random;
}

void applet_dispatch(mz_applet* applet)
{
	srand(time(NULL));
	
	mz_tint background_color = (mz_tint){0, 0, 0, 255};
	mz_tint rand_mod = (mz_tint){0, 0, 0, 255};
	mz_boolean direction = MUZZLE_TRUE;
	
	randomize_modifier(&rand_mod, direction);
	
	while (mz_keep_applet(applet))
	{
		if ((background_color.r >= 255 || background_color.b >= 255 || background_color.g >= 255) ||
			(background_color.r <= 0 || background_color.b <= 0 || background_color.g <= 0))
		{
			printf("Color min/max reached!\n");
			direction = !direction;
			randomize_modifier(&rand_mod, direction);
		}
		
		background_color = TINT_ADD(background_color, rand_mod);
		
		mz_begin_drawing(applet);
			mz_clear_screen(background_color);
		mz_end_drawing(applet);
	}
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [CORE] - Background Colors", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_VSYNC | APPLET_FLAG_RESIZBALE);
	mz_start_applet(&applet, applet_dispatch);
	
	mz_terminate_applet(&applet);
	return 0;
}
