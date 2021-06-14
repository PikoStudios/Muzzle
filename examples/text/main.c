#define MUZZLE_SUPPORT_TEXT
#define MUZZLE_SUPPORT_SPRITES
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet pong;

void OnAppletUpdate()
{
    tint my_color = {84, 84, 84, 255};
    font_manager* manager;
    font roboto = load_font("../roboto.tff", manager);

    while (keep_applet(pong.window_handle))
    {
        begin_drawing();
            clear_screen(my_color);
            draw_text(roboto, "Hello, world!", 30.0f, 30.0f, 12, WHITE, manager);
        end_drawing(&pong);
    }
    
}

int main(void)
{
    pong = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Text Rendering", MUZZLE_FALSE, MUZZLE_FALSE);
    StartApplet(&pong);

    QuitMuzzle(pong);
    return 0;
}
