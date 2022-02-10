#include "shapes/Line.h"

// thickness is not supported on all GPUs
void draw_line(vec2 point1, vec2 point2, float thickness, tint color_drawn)
{
    mzBegin(GL_LINES);
        glLineWidth(thickness);
        mzColor4ub(color_drawn.r, color_drawn.g, color_drawn.b, color_drawn.a);
        mzVertex2f(point1.x, point1.y);
        mzVertex2f(point2.x, point2.y);
    mzEnd();
}

void draw_line_type(line data, tint color_drawn)
{
    draw_line(data.point1, data.point2, data.thickness, color_drawn);
}

void draw_line_slope_intercept_form(vec2 m, float b, vec2 start_point, float jump_size, float thickness, tint color_drawn)
{
    vec2 sum = (vec2)
    {
        (start_point.x + m.x) + jump_size,
        ((start_point.y + b) + m.y) + jump_size
    };

    draw_line((vec2){sum.x, 0}, (vec2){0, sum.y}, thickness, color_drawn);
}