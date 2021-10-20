#define MUZZLE_DEPS
#define MZ_DEPS_COLLISION
#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define K 15

Applet collision;

void OnAppletUpdate()
{

    vec2 mouse_pos;
    vec2 pos = { 0.0f , 0.0f };
    vec2 hitbox = { 30.0f, 30.0f };
    vec2 vel = { 0.0f, 0.0f };
    mz_collision_ray2 test_ray = { { 50.0f, 50.0f}, { 0.0f, 0.0f } };

    rectangle objects[K];
    objects[0] = (rectangle){ 10.0f, 200.0f, 20.0f, 20.0f };
    objects[1] = (rectangle){ 30.0f, 200.0f, 20.0f, 20.0f };
    objects[2] = (rectangle){ 50.0f, 200.0f, 20.0f, 20.0f };
    objects[3] = (rectangle){ 70.0f, 200.0f, 20.0f, 20.0f };
    objects[4] = (rectangle){ 90.0f, 200.0f, 20.0f, 20.0f };
    objects[5] = (rectangle){ 10.0f, 250.0f, 20.0f, 20.0f };
    objects[6] = (rectangle){ 30.0f, 250.0f, 20.0f, 20.0f };
    objects[7] = (rectangle){ 50.0f, 250.0f, 20.0f, 20.0f };
    objects[8] = (rectangle){ 70.0f, 250.0f, 20.0f, 20.0f };
    objects[9] = (rectangle){ 90.0f, 250.0f, 20.0f, 20.0f };

    objects[10] = (rectangle){ 110.0f, 200.0f, 20.0f, 20.0f };
    objects[11] = (rectangle){ 210.0f, 150.0f, 5.0f, 70.0f };

    objects[12] = (rectangle){ 100.0f, 20.0f, 30.0f, 100.0f };
    objects[13] = (rectangle){ 50.0f, 60.0f, 100.0f, 30.0f };

    objects[14] = (rectangle){ 150.0f, 30.0f, 5.0f, 5.0f };

    float delta_time;

    fflush(stdout);

    while (keep_applet(collision.window_handle))
    {
        delta_time = get_delta_time_float();

        test_ray.direction = (vec2){get_mouse_x(&collision) - pos.x, get_mouse_y(&collision) - pos.y};

        if (key_down(&collision, KEY_UP)) vel.y = -50.0f;
        if (key_down(&collision, KEY_DOWN)) vel.y = 50.0f;
        if (key_down(&collision, KEY_RIGHT)) vel.y = 50.0f;
        if (key_down(&collision, KEY_UP)) vel.y = -50.0f;

        mouse_pos = get_mouse_position_vec2(&collision);

        if (mouse_down(&collision, MOUSE_LEFT)) vel = (vec2)
        {
            vel.x + mz_collision_scale(mz_collision_normalize(test_ray.direction),100.0f * delta_time).x, 
            vel.y + mz_collision_scale(mz_collision_normalize(test_ray.direction), 100.0f * delta_time).y
        };

        if (mouse_down(&collision, MOUSE_RIGHT)) test_ray.position = get_mouse_position_vec2(&collision);

        pos = (vec2){pos.x + (vel.x * delta_time), pos.y + (vel.y * delta_time)};
        sr_move_and_slide(objects, K, hitbox, &vel, &pos, delta_time);   


        printf("delta time: %f\r", delta_time);

        update_delta_time();

        begin_drawing();
            clear_screen(GRAY);
            
            // TODO: When draw lines function exist, draw hitbox

            draw_circle_vec2(pos, 10, BLACK);

            for (int i = 0; i < K; i++)
            {
                draw_rectangle(objects[i].x, objects[i].y, objects[i].width, objects[i].height, RED);
                // TODO: When draw lines function exist, draw hitbox
            }         
        end_drawing(&collision);
    }
}

int main(void)
{
    collision = InitializeApplet(SCREEN_WIDTH, SCREEN_HEIGHT, "Muzzle [CORE] - Collision", MUZZLE_FALSE, MUZZLE_TRUE);
    StartApplet(&collision);

    QuitMuzzle(collision);
    return 0;
}