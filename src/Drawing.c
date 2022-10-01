#include "core/Drawing.h"

void begin_drawing()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

void end_drawing(Applet *applet)
{
    #ifdef INTERNAL_MODERN_RENDERER_USAGE
        rlDrawRenderBatchActive();
    #endif
    
    glfwSwapBuffers(applet->window_handle);
    glfwPollEvents();

    glFlush();
}

void clear_screen(tint color_drawn)
{
    float r = (float)(color_drawn.r) / 255;
    float g = (float)(color_drawn.g) / 255;
    float b = (float)(color_drawn.b) / 255;
    float a = (float)(color_drawn.a) / 255;

    glClearColor(r, g, b, a);
}

vec2 get_window_scale_dpi(Applet* applet)
{
    vec2 scale = (vec2){ 1.0f, 1.0f };
    vec2 dpi = (vec2){ 1.0f, 1.0f };

    vec2 window_pos = {0};
    glfwGetWindowPos(applet->window_handle, (int*)(&window_pos.x), (int*)(&window_pos.y));

    int monitor_count = 0;
    GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);

    for (int i = 0; i < monitor_count; i++)
    {
        glfwGetMonitorContentScale(monitors[i], &window_pos.x, &window_pos.y);
        
        int x, y, width, height;
        glfwGetMonitorWorkarea(monitors[i], &x, &y, &width, &height);

        if ((window_pos.x >= x) && (window_pos.x < x + width) && (window_pos.y >= y) && (window_pos.y < y + height))
        {
            scale.x = x;
            scale.y = y;
            break;
        }
    }
    
    return scale;
}

void begin_scissor(Applet* applet, int flag_highdpi, int x, int y, int width, int height)
{
    vec2 scale = get_window_scale_dpi(applet);
    glEnable(GL_SCISSOR_TEST);

#ifdef __APPLE__
    int win_width, win_height;
    glfwGetWindowSize(applet->window_handle, &width, &height);

    glScissor((int)(x * scale.x), (int)(win_width * scale.y - (((y + height) * scale.y))), (int)(width * scale.x), (int)(height * scale.y));
#else
    if (flag_highdpi) glScissor((int)(x * scale.x), (int)(applet->height - (y + height) * scale.y), (int)(width * scale.x), (int)(height * scale.y));
    else glScissor(x, applet->height - (y + height), width, height);
#endif
}

void begin_scissor_vec2(Applet* applet, int flag_highdpi, vec2_i pos, vec2_i size)
{
    begin_scissor(applet, flag_highdpi, pos.x, pos.y, size.x, size.y);
}

void end_scissor()
{
    glDisable(GL_SCISSOR_TEST);
}

void update_viewport(Applet *applet, int w, int h)
{
    glfwGetWindowSize(applet->window_handle, &w,&h);
    if (applet->height != h || applet->width != w)
    {
        applet->height = h;
        applet->width = w;
        glViewport(0,0,applet->width, applet->height);
    }
}

void update_viewport_lite(Applet *applet, int w, int h)
{
    glfwGetWindowSize(applet->window_handle, &w, &h);

    applet->width = w;
    applet->height = h;
    glViewport(0,0, applet->width, applet->height);
}