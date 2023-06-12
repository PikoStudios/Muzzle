#define MUZZLE_DEPS
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet applet;

void OnAppletUpdate()
{   
    while (keep_applet(applet.window_handle))
    {        
        begin_drawing(&applet);
            clear_screen(GRAY);
        end_drawing(&applet);
    }
    
}

int main(void)
{
    applet = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Blank Window", MUZZLE_FALSE, MUZZLE_TRUE, MZ_APPLET_FLAG_NONE);
    StartApplet(&applet);

    QuitMuzzle(applet);
    return 0;
}
