#include "shapes/Rectangle.h"

void draw_rectangle(int x, int y, int width, int height, tint color_drawn)
{ 
    mzBegin(GL_QUADS);
        mzColor4ub(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);
        mzVertex2i(x, y);
        mzVertex2i(x + width, y);
        mzVertex2i(x + width, y + height);
        mzVertex2i(x, y + height);
    mzEnd();
}
void draw_rectangle_rec(rectangle rec, tint color_drawn)
{
    mzBegin(GL_QUADS);
        mzColor4ub(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);
        mzVertex2i(rec.x, rec.y);
        mzVertex2i(rec.x + rec.width, rec.y);
        mzVertex2i(rec.x + rec.width, rec.y + rec.height);
        mzVertex2i(rec.x, rec.y + rec.height);
    mzEnd();
}
void draw_rectangle_vec2(vec2 pos, vec2 size, tint color_drawn)
{
    mzBegin(GL_QUADS);
        mzColor4ub(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);
        mzVertex2f(pos.x, pos.y);
        mzVertex2f(pos.x + size.x, pos.y);
        mzVertex2f(pos.x + size.x, pos.y + size.y);
        mzVertex2f(pos.x, pos.y + size.y);
    mzEnd();
}