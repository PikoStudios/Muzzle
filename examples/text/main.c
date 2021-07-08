#define MUZZLE_DEPS
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet text;

void OnAppletUpdate()
{
    tint my_color = {84, 84, 84, 255};
    font_manager* manager;
    font roboto = load_font("../roboto.ttf", manager, "font");

    while (keep_applet(text.window_handle))
    {
        begin_drawing();
            clear_screen(my_color);
            draw_text(roboto, "Hello, world!", 30.0f, 30.0f, 12, WHITE, manager);
        end_drawing(&text);
    }
    
}

int main(void)
{
    text = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Text Rendering", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&text);

    QuitMuzzle(text);
    return 0;
}
