#include "shapes/Rectangle.h"

void draw_rectangle(int x, int y, int width, int height, tint color_drawn)
{ 
    glBegin(GL_QUADS);
        glColor4ub(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);
        glVertex2i(x, y);
        glVertex2i(x + width, y);
        glVertex2i(x + width, y + height);
        glVertex2i(x, y + height);
    glEnd();
}
void draw_rectangle_rec(rectangle rec, tint color_drawn)
{
    glBegin(GL_QUADS);
        glColor4ub(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);
        glVertex2i(rec.X, rec.Y);
        glVertex2i(rec.X + rec.width, rec.Y);
        glVertex2i(rec.X + rec.width, rec.Y + rec.height);
        glVertex2i(rec.X, rec.Y + rec.height);
    glEnd();
}
void draw_rectangle_vec2(vec2 pos, vec2 size, tint color_drawn)
{
    glBegin(GL_QUADS);
        glColor4ub(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);
        glVertex2f(pos.x, pos.y);
        glVertex2f(pos.x + size.x, pos.y);
        glVertex2f(pos.x + size.x, pos.y + size.y);
        glVertex2f(pos.x, pos.y + size.y);
    glEnd();

}