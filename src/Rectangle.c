#include "shapes/Rectangle.h"

void draw_rectangle(int x, int y, int width, int height, tint color_drawn)
{ 
    rlBegin(RL_QUADS);
        rlColor4ub(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);
        rlVertex2i(x, y);
        rlVertex2i(x + width, y);
        rlVertex2i(x + width, y + height);
        rlVertex2i(x, y + height);
    rlEnd();
}
void draw_rectangle_rec(rectangle rec, tint color_drawn)
{
    rlBegin(RL_QUADS);
        rlColor4ub(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);
        rlVertex2i(rec.X, rec.Y);
        rlVertex2i(rec.X + rec.width, rec.Y);
        rlVertex2i(rec.X + rec.width, rec.Y + rec.height);
        rlVertex2i(rec.X, rec.Y + rec.height);
    rlEnd();
}
void draw_rectangle_vec2(vec2 pos, vec2 size, tint color_drawn)
{
    rlBegin(RL_QUADS);
        rlColor4ub(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);
        rlVertex2f(pos.x, pos.y);
        rlVertex2f(pos.x + size.x, pos.y);
        rlVertex2f(pos.x + size.x, pos.y + size.y);
        rlVertex2f(pos.x, pos.y + size.y);
    rlEnd();

}