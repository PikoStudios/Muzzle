#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet applet;

void OnAppletUpdate()
{
    tint my_color = {84, 84, 84, 255};
    tint white = {255,255,255,255};

    int update_width, update_height;
    while (keep_applet(applet.window_handle))
    {
        update_viewport(&applet, update_width, update_height); // <-- required so opengl knows the new size and where to draw to
        begin_drawing();
            clear_screen(my_color);
            draw_rectangle(50,50,120,120,white);
        end_drawing(&applet);
    }
    
}

int main(void)
{
    applet = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Resizing Windows", MUZZLE_TRUE, MUZZLE_FALSE);
    StartApplet(&applet);

    QuitMuzzle(applet);
    return 0;
}
