#define MUZZLE_DEPS
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet applet;

void OnAppletUpdate()
{

#ifdef MUZZLE_COMPILE_AS_TEST
    int frame_counter = 0;
#endif
    
    while (keep_applet(applet.window_handle))
    {
#ifdef MUZZLE_COMPILE_AS_TEST
        if (frame_counter++ >= 1000) exit(0);
#endif
        
        begin_drawing();
            clear_screen(GRAY);
        end_drawing(&applet);
    }
    
}

int main(void)
{
    applet = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Blank Window", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&applet);

    QuitMuzzle(applet);
    return 0;
}
