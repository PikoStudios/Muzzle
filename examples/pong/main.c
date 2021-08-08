#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet applet;

typedef struct Ball 
{
    vec2 pos;
    vec2 size;
    float velocity;
} Ball;



void OnAppletUpdate()
{
    tint my_color = {84, 84, 84, 255};
    rectangle rect1 = 
    {
        .X=5,
        .Y=SCREEN_HEIGHT/2-150,
        .height=300,
        .width=15
    };

    rectangle rect2 =
    {
        .X=1260,
        .Y=SCREEN_HEIGHT/2-150,
        .width=15,
        .height=300
    };

    bool start = false;
    Ball ball;
    

    while (keep_applet(applet.window_handle))
    {
        // Update
        if (key_down(&applet, KEY_W)) rect1.Y -= 5;
        if (key_down(&applet, KEY_S)) rect1.Y += 5;
        if (key_down(&applet, KEY_UP)) rect2.Y -= 5;
        if (key_down(&applet, KEY_DOWN)) rect2.Y += 5;

        if (ball.pos.y <= SCREEN_HEIGHT) ball.velocity += 2.0f;

        begin_drawing();
            clear_screen(BLACK);
            draw_rectangle_rec(rect1, WHITE);
            draw_rectangle_rec(rect2, WHITE);
        end_drawing(&applet);
    }
    
}

int main(void)
{
    applet = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Blank Window", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&applet);

    QuitMuzzle(applet);
    return 0;
}
