#define MUZZLE_SUPPORT_SPRITES
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
        begin_drawing();
            clear_screen(my_color);

            if (key_down(&applet, KEY_A)) log_status(STATUS_INFO, "A was pressed");
            if (mouse_down(&applet, MOUSE_LEFT)) log_status(STATUS_INFO, "Left mouse was pressed");
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
