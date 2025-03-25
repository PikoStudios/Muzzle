#include "core/applet.h"
#include "core/shader.h"
#include "core/vector.h"
#include "primitives/rectangle.h"
#include <Muzzle.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MAX_DEPTH 3.5f

void applet_loop(mz_applet* applet)
{
    mz_shader shader_pass = mz_load_shader("../vert.glsl", "../frag.glsl", SHADER_TYPE_PASS);
    float depth = MAX_DEPTH;
    int depth_mult = 1;

    mz_upload_uniform_vec2(shader_pass, "uScreenResolution", (mz_vec2){SCREEN_WIDTH, SCREEN_HEIGHT});

    while (mz_keep_applet(applet))
    {
        if (depth >= MAX_DEPTH || depth <= -MAX_DEPTH)
        {
            depth_mult = -depth_mult;
        }

        depth += applet->delta_time * depth_mult;

        mz_upload_uniform_float(shader_pass, "uDepth", depth);

        mz_begin_drawing(applet);
            mz_clear_screen(TINT_WHITE);
            mz_use_shader_pass(applet, shader_pass);
        mz_end_drawing(applet);
    }

    mz_unload_shader(shader_pass);
}

int main(void)
{
    mz_applet applet = mz_initialize_applet("Muzzle [EXAMPLE] :: Mandelbrot Fractal", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_VSYNC | APPLET_FLAG_TRACK_DELTA_TIME);
    mz_start_applet(&applet, applet_loop);

    mz_terminate_applet(&applet);
    return 0;
}
