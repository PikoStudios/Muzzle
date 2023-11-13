#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void OnAppletUpdate(Applet* applet)
{
	while (keep_applet(applet))
	{
		begin_drawing(applet);
			clear_screen(GRAY);
			draw_rectangle(300.f, 300.f, 50.f, 50.f, WHITE);
		end_drawing(applet);
	}
}

int main(void)
{
	Applet applet = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Blank Window", MZ_APPLET_VSYNC | MZ_APPLET_RESIZABLE);
	StartApplet(&applet);
	
	QuitMuzzle(&applet);
	return 0;
}