#define MUZZLE_SUPPORT_SPRITES
//#define MUZZLE_VERBOSE
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet pong;

void OnAppletUpdate()
{
    tint my_color = {84, 84, 84, 255};
    sprite spr = load_sprite("../spr.png"); // Upload sprite into GPU
    

    while (keep_applet(pong.window_handle))
    {
        begin_drawing();
            clear_screen(my_color);

            draw_sprite(&spr, 10,10, 1.0f, 0.0f, WHITE);
        end_drawing(&pong);
    }
    
    unload_sprite(&spr); //Unload Sprite from GPU
}

int main(void)
{
    pong = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Blank Window", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&pong);

    QuitMuzzle(pong);
    return 0;
}
