#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet blank_window;

void OnAppletUpdate()
{
    tint my_color = {84, 84, 84, 255};
    float rad = 5.0f;

    while (keep_applet(blank_window.window_handle))
    {
        begin_drawing();
            clear_screen(my_color);
            draw_rectangle(50,50,120,120,WHITE);

            rad += 0.5f;
            draw_circle(500,500, rad, USAF_BLUE);
        end_drawing(&blank_window);
    }
    
}

int main(void)
{
    blank_window = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Circle", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&blank_window);

    QuitMuzzle(blank_window);
    return 0;
}
