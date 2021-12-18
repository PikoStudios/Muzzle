#define MUZZLE_DEPS
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet applet;

void OnAppletUpdate()
{
    line my_line;
    my_line.point1 = (vec2)
    {
        100,
        250
    };

    my_line.point2 = (vec2)
    {
        260,
        300
    };

    my_line.thickness = 1.f;

    while (keep_applet(applet.window_handle))
    {
        begin_drawing();
            clear_screen(GRAY);
            draw_line_type(my_line, YELLOW);
        end_drawing(&applet);

        if (key_down(&applet, KEY_EQUAL))
        {
            my_line.thickness += 5.f;
            printf("%.2f\n", my_line.thickness);
        }
        else if (key_down(&applet, KEY_MINUS))
        {
            my_line.thickness -= 5.f;
            printf("%.2f\n", my_line.thickness);
        }
    }
    
}

int main(void)
{
    applet = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Blank Window", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&applet);

    QuitMuzzle(applet);
    return 0;
}
