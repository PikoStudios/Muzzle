#pragma once
#include "../backend.h"
#include "../core/vector.h"
#include "../core/tint.h"

struct _mz_line
{
    vec2 point1;
    vec2 point2;
    float thickness; // thickness is not supported on all gpus
};

typedef struct _mz_line line;

void draw_line(vec2 point1, vec2 point2, float thickness, tint color_drawn);
void draw_line_type(line data, tint color_drawn);

// for people that havent taken algebra 1 yet, slope intercept form is y = mx+b, m is rise over run.
void draw_line_slope_intercept_form(vec2 m, float b, vec2 start_point, float jump_size, float thickness, tint color_drawn);