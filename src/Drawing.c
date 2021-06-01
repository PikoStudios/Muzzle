#include "core/Drawing.h"

void begin_drawing()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}
void end_drawing(Applet *applet)
{
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