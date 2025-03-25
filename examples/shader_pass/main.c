#include "core/font.h"
#include "core/shader.h"
#include "input/key.h"
#include "primitives/sprite.h"
#include <Muzzle.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define WAIT_FOR_KEY_RELEASE(k) while (!mz_key_released(applet, k)) {glfwPollEvents();}

void applet_loop(mz_applet* applet)
{
    mz_font font = mz_load_font(applet, "../assets/OpenSans-Regular.ttf");
    mz_sprite sprite = mz_load_sprite("../assets/muzzle_logo.png");

    mz_shader color_filter = mz_load_shader("../shaders/cf_vert.glsl", "../shaders/cf_frag.glsl", SHADER_TYPE_PASS);
    mz_boolean color_filter_active = MUZZLE_FALSE;

    mz_shader grayscale_filter = mz_load_shader("../shaders/gs_vert.glsl", "../shaders/gs_frag.glsl", SHADER_TYPE_PASS);
    mz_boolean grayscale_filter_active = MUZZLE_FALSE;

    mz_shader shear_filter = mz_load_shader("../shaders/sh_vert.glsl", "../shaders/sh_frag.glsl", SHADER_TYPE_PASS);
    mz_boolean shear_filter_active = MUZZLE_FALSE;

    float time = 0.0f;

    while (mz_keep_applet(applet))
    {
        time += applet->delta_time;
        mz_upload_uniform_float(color_filter, "uTime", time);

        if (mz_key_pressed(applet, KEY_ONE))
        {
            color_filter_active = !color_filter_active;
            WAIT_FOR_KEY_RELEASE(KEY_ONE);
        }

        else if (mz_key_pressed(applet, KEY_TWO))
        {
            grayscale_filter_active = !grayscale_filter_active;
            WAIT_FOR_KEY_RELEASE(KEY_TWO);
        }

        else if (mz_key_pressed(applet, KEY_THREE))
        {
            shear_filter_active = !shear_filter_active;
            WAIT_FOR_KEY_RELEASE(KEY_THREE);
        }

        mz_begin_drawing(applet);
            mz_clear_screen(TINT_WHITE);

            if (color_filter_active) mz_use_shader_pass(applet, color_filter);
            if (grayscale_filter_active) mz_use_shader_pass(applet, grayscale_filter);
            if (shear_filter_active) mz_use_shader_pass(applet, shear_filter);

            mz_draw_sprite(applet, &sprite, (float)(applet->width - sprite.width) / 2, (float)(applet->height - sprite.height) / 2, TINT_WHITE);

            mz_draw_text(applet, "Press 1 to toggle color filter", 40, applet->height - 200, 36.f, &font, TINT_BLACK);
            mz_draw_text(applet, "Press 2 to toggle grayscale filter", 40, applet->height - 164, 36.f, &font, TINT_BLACK);
            mz_draw_text(applet, "Press 3 to toggle shear filter", 40, applet->height - 128, 36.f, &font, TINT_BLACK);

            mz_draw_rectangle(applet, 50, 50, 50, 50, TINT_ORANGE);
        mz_end_drawing(applet);
    }

    mz_unload_shader(color_filter);
    mz_unload_shader(grayscale_filter);
    mz_unload_shader(shear_filter);

    mz_unload_sprite(&sprite);
    mz_unload_font(&font);
}

int main(void)
{
    mz_applet applet = mz_initialize_applet("Muzzle [CORE] :: Shader Pass", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_RESIZBALE | APPLET_FLAG_VSYNC | APPLET_FLAG_TRACK_DELTA_TIME);
    mz_start_applet(&applet, applet_loop);

    mz_terminate_applet(&applet);
    return 0;
}
