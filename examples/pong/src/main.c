#define MUZZLE_DEPS
#define MZ_EXCLUDE_AUDIO

#include <Muzzle.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define EMPTY_STRING ""
// #define GAME_OVER NULL
Applet applet;





bool isGameOver;
bool check_collision_point_rec(vec2 point, rectangle rec)
{
    if ((point.x >= rec.x) && (point.x <= (rec.x + rec.width)) && (point.y >= rec.y) && (point.y <= (rec.y + rec.height))) return true;
    return false;
}

void draw_ball(circle ball)
{
    draw_circle_type(ball, WHITE);
}
#define DEBUG

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

void OnAppletUpdate()
{


    // while(isGameOver) {
    //     draw_text()
    // }
    circle ball = {
        .radius = 5,
        .x = SCREEN_WIDTH / 2,
        .y = SCREEN_HEIGHT / 2
    };

    enum direction ball_direction_x = LEFT; // Initialized it as LEFT
    enum direction ball_direction_y = DOWN;
    enum players last_player_collision;
    //int paused = 0;

    int p1, p2 = 0;

    rectangle player = {
        .height = 250,
        .width = 25,
        .x = 25,
        .y = 25
    };

    rectangle player2 = {
        .height = 250,
        .width = 25,
        .x = 1230,
        .y = 25
    };

    vec2 p1_point_counter_position = (vec2)
    {
        .x = player.x,
        .y = player.y
    };

    vec2 p2_point_counter_position = (vec2)
    {
        .x = player2.x,
        .y = player2.y
    };
    font p2sp = load_font("../font.ttf", "p2sp");
    char buf_p1[1024] = EMPTY_STRING;
    char buf_p2[1024] = EMPTY_STRING;
    while (keep_applet(applet.window_handle))
    {

        sprintf(buf_p1, "%i", p1);
        sprintf(buf_p2, "%i", p2);

        if (key_down(&applet, KEY_W)) player.y -= 5;
        if (key_down(&applet, KEY_S)) player.y += 5;
        if (key_down(&applet, KEY_UP)) player2.y -= 5;
        if (key_down(&applet, KEY_DOWN)) player2.y += 5;
        

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
                }
            }

            if (ball.x < player.x || ball.x > player2.x) 
            {
                 isGameOver = true;
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
                }
                ball_direction_x = RIGHT;
            } 

            if (check_collision_point_rec((vec2){.x=ball.x, .y=ball.y}, player))
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
                }
            }

            if (ball.x < player.x  || ball.x > player2.x) 
            {

                isGameOver = true;
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
                }
                ball_direction_x = LEFT;
            } 

            if (check_collision_point_rec((vec2){.x=ball.x, .y=ball.y}, player2))
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

        begin_drawing();
            clear_screen(BLACK);
            draw_text(p2sp, buf_p1, p1_point_counter_position.x, p1_point_counter_position.y + 650, 35, WHITE);
            draw_text(p2sp, buf_p2, p2_point_counter_position.x, p2_point_counter_position.y + 650, 35, WHITE);
            if(isGameOver) {
                draw_text(p2sp, "Game Over", SCREEN_WIDTH / 2 -190, SCREEN_HEIGHT / 2 + 300, 35, WHITE);
            }
            //if (paused) draw_text(p2sp, "Press Space", SCREEN_WIDTH / 2 - 15, 10, 20, WHITE);

            draw_rectangle_rec(player, WHITE);
            draw_rectangle_rec(player2, WHITE);
            draw_ball(ball);

        end_drawing(&applet);

    }
    
}

int main(void)
{
    applet = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [EXAMPLE] - Pong", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&applet);

    QuitMuzzle(applet);
    return 0;
}
