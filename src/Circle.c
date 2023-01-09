#include "shapes/Circle.h"

void draw_circle(int x, int y, float radius, tint color_drawn)
{
    if (radius <= 0) radius = 0.1f;
    glBegin(GL_TRIANGLE_FAN);
      glColor4ub(color_drawn.r,color_drawn.g,color_drawn.b, color_drawn.a);
      glVertex2f(x,y);

        for (int i = 0; i <= 360; i++)
        {
            glVertex2f(x + sin(DEG2RAD*i) * radius, y + cos(DEG2RAD*i) * radius);
        }
    glEnd();
    
}
void draw_circle_type(circle data, tint color_drawn)
{
    draw_circle(data.x, data.y, data.radius, color_drawn);
}
void draw_circle_vec2(vec2 pos, float radius, tint color_drawn)
{
    draw_circle((int)(pos.x), (int)(pos.y), radius, color_drawn);
}