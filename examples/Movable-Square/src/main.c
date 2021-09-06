#define MUZZLE_DEPS 
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

Applet applet;

void OnAppletUpdate()
{
   rectangle player = {
        .height = 50,
        .width = 50,
        .x = 225,
        .y = 225
    };

    while (keep_applet(applet.window_handle))
    {
        begin_drawing();
            clear_screen(GRAY);
                if(key_down(&applet, KEY_W)&&player.y!=5) player.y -=5;
                else if(key_down(&applet, KEY_S)&&player.y!=495&&player.y!=490) player.y +=5;
                else if(key_down(&applet, KEY_A)&&player.x!=5) player.x -=5;
                else if(key_down(&applet, KEY_D)&&player.x!=495&&player.x!=490) player.x +=5;
                draw_rectangle_rec(player,WHITE);
        end_drawing(&applet);
    }
    
}

int main(void)
{
    applet = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [EXAMPLE] - Movable Square", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&applet);

    QuitMuzzle(applet);
    return 0;
}