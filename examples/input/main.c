#define MUZZLE_SUPPORT_SPRITES
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet pong;

void OnAppletUpdate()
{
    tint my_color = {84, 84, 84, 255};

    while (keep_applet(pong.window_handle))
    {
        begin_drawing();
            clear_screen(my_color);

            if (key_down(&pong, KEY_A)) log_status(STATUS_INFO, "A was pressed");
            if (mouse_down(&pong, MOUSE_LEFT)) log_status(STATUS_INFO, "Left mouse was pressed");
        end_drawing(&pong);
    }
    
}

int main(void)
{
    pong = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Blank Window", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&pong);

    QuitMuzzle(pong);
    return 0;
}
