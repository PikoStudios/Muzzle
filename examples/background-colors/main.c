#include <Muzzle.h>
#include <stdio.h>
#include <time.h>
#define RANDINT(min, max) (rand() % (max - min + 1)) + min
#define TINT_ADD(t1, t2) (tint){t1.r + t2.r, t1.b + t2.b, t1.g + t2.g, t1.a}
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void randomize_modifier(tint* modifier, mz_boolean positive)
{
	int random = positive ? RANDINT(1, 2) : RANDINT(-2, 1);
	
	modifier->r = random;
	modifier->g = random;
	modifier->b = random;
}

void OnAppletUpdate(Applet* applet)
{
	srand(time(NULL));
	
	tint background_color = (tint){0, 0, 0, 255};
	tint rand_mod = (tint){0, 0, 0, 255};
	mz_boolean direction = MUZZLE_TRUE;
	
	randomize_modifier(&rand_mod, direction);
	
	while (keep_applet(applet))
	{
		if ((background_color.r >= 255 || background_color.b >= 255 || background_color.g >= 255) ||
			(background_color.r <= 0 || background_color.b <= 0 || background_color.g <= 0))
		{
			printf("Color min/max reached!\n");
			direction = !direction;
			randomize_modifier(&rand_mod, direction);
		}
		
		background_color = TINT_ADD(background_color, rand_mod);
		
		begin_drawing(applet);
			clear_screen(background_color);
		end_drawing(applet);
	}
}

int main(void)
{
	Applet applet = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Background Colors", MZ_APPLET_VSYNC | MZ_APPLET_RESIZABLE);
	StartApplet(&applet);
	
	QuitMuzzle(&applet);
	return 0;
}