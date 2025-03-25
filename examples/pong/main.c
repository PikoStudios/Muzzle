#include "core/shader.h"
#include <Muzzle.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define EMPTY_STRING ""

#ifndef ASSETS_DIR
    #define ASSETS_DIR "../"
#endif

#define WINDOW_TITLE "Muzzle [EXAMPLES] - Pong"

bool check_collision_point_rec(mz_circle point, mz_rectangle rec)
{
    if ((point.x >= rec.x) && (point.x <= (rec.x + rec.width)) && (point.y >= rec.y) && (point.y <= (rec.y + rec.height))) return true;
    return false;
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
    mz_shader color_filter = mz_load_shader("../vert.glsl", "../frag.glsl", SHADER_TYPE_PASS);
    float time = 0.0f;

    mz_circle ball =
    {
        .radius = 10,
        .x = SCREEN_WIDTH / 2,
        .y = SCREEN_HEIGHT / 2    
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

    while (mz_keep_applet(applet))
    {
        time += applet->delta_time;
        mz_upload_uniform_float(color_filter, "uTime", time);

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
        printf("ball { x: %i, x.directon: %i, y: %i, y.directon: %i, } player { x: %f, y: %f }\r", ball.x, ball_direction_x, ball.y, ball_direction_y, player.x, player.y);
#endif
        // Physics

        switch (ball_direction_x)
        {
        case LEFT:
        //if (!paused)
        //{
            // Hit Edge on Y
            if (ball.y >= 720 || ball.y <= 5)
            { // Invert
                if (ball.y <= 5) ball.y += 5;
                else ball.y -= 5;
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

            if (ball.x < player.x || ball.x > player2.x) 
            {
                p2++;
                ball.x = SCREEN_WIDTH / 2;
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

            if (check_collision_point_rec(ball, player))
            {
                ball.x += 5; 
                ball_direction_x = RIGHT;
                break;
            }

            ball.x -= 5;
            if (ball_direction_y == UP) ball.y -= 5;
            else if (ball_direction_y == DOWN) ball.y += 5;

            break;
        //}

        case RIGHT:
        //if (!paused)
        //{
            if (ball.y >= 720 || ball.y <= 5)
            { // Invert
                if (ball.y <= 5) ball.y += 5;
                else ball.y -= 5;
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

            if (ball.x < player.x  || ball.x > player2.x) 
            {
                p1++;
                ball.x = SCREEN_WIDTH / 2;
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

            if (check_collision_point_rec(ball, player2))
            {
                ball.x -= 5;
                ball_direction_x = LEFT;
                break;
            }

            ball.x += 5;
            if (ball_direction_y == UP) ball.y -= 5;
            else if (ball_direction_y == DOWN) ball.y += 5;
            break;
        //}

        default:
            break;
        }

        mz_begin_drawing(applet);
            mz_clear_screen(TINT_BLACK);
            mz_use_shader_pass(applet, color_filter);

            //draw_text(p2sp, buf_p1, p1_point_counter_position.x, p1_point_counter_position.y + 650, 35, WHITE);
            //draw_text(p2sp, buf_p2, p2_point_counter_position.x, p2_point_counter_position.y + 650, 35, WHITE);

            //if (paused) draw_text(p2sp, "Press Space", SCREEN_WIDTH / 2 - 15, 10, 20, WHITE);

            mz_draw_rectangle_type(applet, player, TINT_WHITE);
            mz_draw_rectangle_type(applet, player2, TINT_WHITE);
            mz_draw_circle_type(applet, ball, TINT_WHITE);

        mz_end_drawing(applet);

    }
}

int main(void)
{
    mz_applet applet = mz_initialize_applet(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_VSYNC | APPLET_FLAG_TRACK_DELTA_TIME);
    mz_start_applet(&applet, applet_dispatch);

    mz_terminate_applet(&applet);
    return 0;
}
