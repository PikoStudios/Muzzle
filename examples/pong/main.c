#include "core/applet.h"
#include "core/drawing.h"
#include "input/key.h"
#include "primitives/rectangle.h"
#include "primitives/sprite.h"
#include <Muzzle.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <winnt.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define EMPTY_STRING ""

#ifndef ASSETS_DIR
    #define ASSETS_DIR "../"
#endif

#define WINDOW_TITLE "Muzzle [EXAMPLES] - Pong"

bool check_collision_point_rec(mz_vec2 point, mz_rectangle rec)
{
    if ((point.x >= rec.x) && (point.x <= (rec.x + rec.width)) && (point.y >= rec.y) && (point.y <= (rec.y + rec.height))) return true;
    return false;
}

// Will be removed when circles are added to Muzzle 3
typedef struct ball
{
    mz_vec2 position;
    mz_tint tint;
    float radius;
} ball;

void draw_ball(mz_applet* applet, ball ball, mz_sprite* ball_sprite)
{
    mz_draw_sprite(applet, ball_sprite, ball.position.x - (ball_sprite->width * 0.5), ball.position.y - (ball_sprite->height * 0.5), ball.tint);
}
//#define DEBUG

enum direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum players
{
    p1,
    p2
};

void applet_dispatch(mz_applet* applet)
{
    ball ball =
    {
        .radius = 5,
        .position = {.x = SCREEN_WIDTH / 2, .y = SCREEN_HEIGHT / 2},
        .tint = TINT_WHITE
    };

    enum direction ball_direction_x = LEFT; // Initialized it as LEFT
    enum direction ball_direction_y = DOWN;
    enum players last_player_collision;
    //int paused = 0;

    int p1 = 0, p2 = 0;

    mz_rectangle player =
    {
        .height = 250,
        .width = 25,
        .x = 25,
        .y = 25
    };

    mz_rectangle player2 =
    {
        .height = 250,
        .width = 25,
        .x = 1230,
        .y = 25
    };

    mz_vec2 p1_point_counter_position =
    {
        .x = player.x,
        .y = player.y
    };

    mz_vec2 p2_point_counter_position =
    {
        .x = player2.x,
        .y = player2.y
    };

    //font p2sp = load_font("../font.ttf", "p2sp");
    //char buf_p1[1024] = EMPTY_STRING;
    //char buf_p2[1024] = EMPTY_STRING;

    char title_buffer[1024];
    memset(title_buffer, 0, 1024);

    mz_sprite ball_sprite = mz_load_sprite(ASSETS_DIR "circle.png");

    while (mz_keep_applet(applet))
    {
        snprintf(title_buffer, 1024, WINDOW_TITLE " Score: %d-%d", p1, p2);
        printf("Player 1 Score: %d. Player 2 Score: %d\r", p1, p2);

        mz_update_window_title(applet, title_buffer);

        if (mz_key_pressed(applet, KEY_W)) player.y -= 5;
        if (mz_key_pressed(applet, KEY_S)) player.y += 5;
        if (mz_key_pressed(applet, KEY_UP)) player2.y -= 5;
        if (mz_key_pressed(applet, KEY_DOWN)) player2.y += 5;
        

        if (player.y >= 470 || player.y <= 0)
        {
            if (player.y <= 5) player.y += 5;
            else player.y -= 5;
        }

        if (player2.y >= 470 || player2.y <= 0)
        {
            if (player2.y <= 0) player2.y += 5;
            else player2.y -= 5;
        }

#ifdef DEBUG
        printf("ball { x: %i, x.directon: %i, y: %i, y.directon: %i, } player { x: %f, y: %f }\r", ball.position.x, ball_direction_x, ball.position.y, ball_direction_y, player.x, player.y);
#endif
        // Physics

        switch (ball_direction_x)
        {
        case LEFT:
        //if (!paused)
        //{
            // Hit Edge on Y
            if (ball.position.y >= 720 || ball.position.y <= 5)
            { // Invert
                if (ball.position.y <= 5) ball.position.y += 5;
                else ball.position.y -= 5;
                switch (ball_direction_y)
                {
                case UP:
                    ball_direction_y = DOWN;
                    break;
                
                case DOWN:
                    ball_direction_y = UP;
                    break;

                default:
                    break;
                }
            }

            if (ball.position.x < player.x || ball.position.x > player2.x) 
            {
                p2++;
                ball.position.x = SCREEN_WIDTH / 2;
                switch (ball_direction_y)
                {
                case UP:
                    ball_direction_y = DOWN;
                    break;
                
                case DOWN:
                    ball_direction_y = UP;
                    break;

                default:
                    break;
                }
                ball_direction_x = RIGHT;
            } 

            if (check_collision_point_rec(ball.position, player))
            {
                ball.position.x += 5; 
                ball_direction_x = RIGHT;
                break;
            }

            ball.position.x -= 5;
            if (ball_direction_y == UP) ball.position.y -= 5;
            else if (ball_direction_y == DOWN) ball.position.y += 5;

            break;
        //}

        case RIGHT:
        //if (!paused)
        //{
            if (ball.position.y >= 720 || ball.position.y <= 5)
            { // Invert
                if (ball.position.y <= 5) ball.position.y += 5;
                else ball.position.y -= 5;
                switch (ball_direction_y)
                {
                case UP:
                    ball_direction_y = DOWN;
                    break;
                
                case DOWN:
                    ball_direction_y = UP;
                    break;

                default:
                    break;
                }
            }

            if (ball.position.x < player.x  || ball.position.x > player2.x) 
            {
                p1++;
                ball.position.x = SCREEN_WIDTH / 2;
                switch (ball_direction_y)
                {
                case UP:
                    ball_direction_y = DOWN;
                    break;
                
                case DOWN:
                    ball_direction_y = UP;
                    break;

                default:
                    break;
                }
                ball_direction_x = LEFT;
            } 

            if (check_collision_point_rec(ball.position, player2))
            {
                ball.position.x -= 5;
                ball_direction_x = LEFT;
                break;
            }

            ball.position.x += 5;
            if (ball_direction_y == UP) ball.position.y -= 5;
            else if (ball_direction_y == DOWN) ball.position.y += 5;
            break;
        //}

        default:
            break;
        }

        mz_begin_drawing(applet);
            mz_clear_screen(TINT_BLACK);
            //draw_text(p2sp, buf_p1, p1_point_counter_position.x, p1_point_counter_position.y + 650, 35, WHITE);
            //draw_text(p2sp, buf_p2, p2_point_counter_position.x, p2_point_counter_position.y + 650, 35, WHITE);

            //if (paused) draw_text(p2sp, "Press Space", SCREEN_WIDTH / 2 - 15, 10, 20, WHITE);

            mz_draw_rectangle_type(applet, player, TINT_WHITE);
            mz_draw_rectangle_type(applet, player2, TINT_WHITE);
            draw_ball(applet, ball, &ball_sprite);

        mz_end_drawing(applet);

    }

    mz_unload_sprite(&ball_sprite);
}

int main(void)
{
    mz_applet applet = mz_initialize_applet(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_VSYNC | APPLET_FLAG_TRACK_DELTA_TIME);
    mz_start_applet(&applet, applet_dispatch);

    mz_terminate_applet(&applet);
    return 0;
}
