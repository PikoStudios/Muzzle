#define MUZZLE_INCLUDE_CALLBACK_HOOK_API
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void resize_hook(Applet* applet, int width, int height)
{
	printf("Window Resized! New size = <%d,%d>\n", width, height);
}

void OnAppletUpdate(Applet* applet)
{
	muzzle_register_callback(MUZZLE_CALLBACK_HOOK_REISZE, (union callback_hook_union){.resize_fptr=resize_hook});
	
	while (keep_applet(applet))
	{
		begin_drawing(applet);
			clear_screen(GRAY);
		end_drawing(applet);
	}
}

int main(void)
{
	Applet applet = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Callback Hook", MZ_APPLET_VSYNC | MZ_APPLET_RESIZABLE);
	StartApplet(&applet);
	
	QuitMuzzle(&applet);
	return 0;
}