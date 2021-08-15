#define MUZZLE_DEPS
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

Applet applet;

void OnAppletUpdate()
{
    rectangle main_platform  = {
        .height=10,
        .width=100,
        .x=200,
        .y=300
    };
    rectangle player = {
        .height=50,
        .width=50,
        .x=225,
        .y=100
    };
   
    while (keep_applet(applet.window_handle))
    {
        begin_drawing();
            clear_screen(GRAY);
            draw_rectangle_rec(main_platform, WHITE);
            if(player.y+player.height<main_platform.y){
                player.y+=1;
            }
                draw_rectangle(player.x, player.y, player.width, player.height, RED);
                

        end_drawing(&applet);
    }
    
}

int main(void)
{
    applet = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Blank Window", MUZZLE_FALSE, MUZZLE_FALSE);
    StartApplet(&applet);

    QuitMuzzle(applet);
    return 0;
}