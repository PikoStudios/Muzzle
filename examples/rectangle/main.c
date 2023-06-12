#define MUZZLE_DEPS
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet applet;

void OnAppletUpdate()
{
    tint my_color = {84, 84, 84, 255};
    
    while (keep_applet(applet.window_handle))
    {   
        begin_drawing(&applet);
            clear_screen(my_color);
            draw_rectangle(&applet,50,50,120,120,BLACK);
        end_drawing(&applet);
    }
    
}

int main(void)
{
    applet = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Rectangle", MUZZLE_FALSE, MUZZLE_TRUE, MZ_APPLET_FLAG_NONE);
    StartApplet(&applet);

    QuitMuzzle(applet);
    return 0;
}
