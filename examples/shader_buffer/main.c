#include <Muzzle.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void applet_loop(mz_applet* applet)
{
    float data[] = {0.f, 0.25f, 0.5f, 0.75f, 1.f};

    mz_shader shader = mz_load_shader("../vert.glsl", "../frag.glsl", SHADER_TYPE_PASS);
    mz_shader_buffer buffer = mz_create_shader_buffer(1, data, sizeof(data));

    float time = 0.0f;

    while (mz_keep_applet(applet))
    {
        time += applet->delta_time;

        mz_upload_uniform_float(shader, "uTime", time);

        mz_begin_drawing(applet);
            mz_clear_screen(TINT_WHITE);
            mz_use_shader_pass(applet, shader);
        mz_end_drawing(applet);
    }
}

int main(void)
{
    mz_applet applet = mz_initialize_applet("Muzzle [SHADER] - Shader Buffer", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_RESIZBALE | APPLET_FLAG_VSYNC | APPLET_FLAG_TRACK_DELTA_TIME);
    mz_start_applet(&applet, applet_loop);

    mz_terminate_applet(&applet);
    return 0;
}
