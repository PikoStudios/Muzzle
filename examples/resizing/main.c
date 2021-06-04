#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet pong;

void OnAppletUpdate()
{
    tint my_color = {84, 84, 84, 255};
    tint white = {255,255,255,255};

    int update_width, update_height;
    while (keep_applet(pong.window_handle))
    {
        update_viewport(&pong, update_width, update_height); // <-- required so opengl knows the new size and where to draw to
        begin_drawing();
            clear_screen(my_color);
            draw_rectangle(50,50,120,120,white);
        end_drawing(&pong);
    }
    
}

int main(void)
{
    pong = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Resizing Windows", MUZZLE_TRUE, MUZZLE_FALSE);
    StartApplet(&pong);

    QuitMuzzle(pong);
    return 0;
}
