#define MUZZLE_DEPS
#include <Muzzle.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Applet applet;

bool check_collision_point_rec(vec2 point, rectangle rec)
{
    if ((point.x >= rec.x) && (point.x <= (rec.x + rec.width)) && (point.y >= rec.y) && (point.y <= (rec.y + rec.height))) return true;
    return false;
}

void draw_ball(circle ball)
{
    draw_circle_type(ball, WHITE);
}

void OnAppletUpdate()
{
    circle ball = {
        .radius = 5,
        .x = 50,
        .y = 50
    };

    rectangle player = {
        .height = 25,
        .width = 25,
        .x = 25,
        .y = 25
    };


    while (keep_applet(applet.window_handle))
    {
        if (check_collision_point_rec((vec2){.x=ball.x, .y=ball.y}, player)) log_status(STATUS_INFO, "collision!");

        if (key_down(&applet, KEY_W)) player.y -= 5;
        if (key_down(&applet, KEY_S)) ball.y += 5;

        begin_drawing();
            clear_screen(BLACK);
            draw_rectangle_rec(player, WHITE);
            draw_ball(ball);
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
