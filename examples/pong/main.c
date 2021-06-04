#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet pong;

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
    

    while (keep_applet(pong.window_handle))
    {
        // Update
        if (key_down(&pong, KEY_W)) rect1.Y -= 5;
        if (key_down(&pong, KEY_S)) rect1.Y += 5;
        if (key_down(&pong, KEY_UP)) rect2.Y -= 5;
        if (key_down(&pong, KEY_DOWN)) rect2.Y += 5;

        if (ball.pos.y <= SCREEN_HEIGHT) ball.velocity += 2.0f;

        begin_drawing();
            clear_screen(BLACK);
            draw_rectangle_rec(rect1, WHITE);
            draw_rectangle_rec(rect2, WHITE);
        end_drawing(&pong);
    }
    
}

int main(void)
{
    pong = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Blank Window", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&pong);

    QuitMuzzle(pong);
    return 0;
}
