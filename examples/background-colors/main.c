#include <Muzzle.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void applet_dispatch(mz_applet* applet)
{
	float time = 0.0f;
	
	while (mz_keep_applet(applet))
	{
		time += 0.01f;

		mz_tint tint = (mz_tint)
		{
			((sin(time) + 1) * 0.5) * 255,
			((sin(time + 2.0f * M_PI / 3.0f) + 1) * 0.5) * 255,
			((sin(time + 4.0f * M_PI / 3.0f) + 1) * 0.5) * 255,
			255
		};
		
		mz_begin_drawing(applet);
			mz_clear_screen(tint);
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
