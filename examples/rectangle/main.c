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
            draw_rectangle(50,50,120,120,WHITE);
        end_drawing(&pong);
    }
    
}

int main(void)
{
    pong = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Rectangle", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&pong);

    QuitMuzzle(pong);
    return 0;
}
