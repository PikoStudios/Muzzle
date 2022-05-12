#pragma once
#include "../backend.h"
#include "tint.h"
#include "vector.h"
#include "Applet.h"

#ifdef __cplusplus
extern "C" {
#endif

void begin_scissor(Applet* applet, int flag_highdpi, int x, int y, int width, int height);
void begin_scissor_vec2(Applet* applet, int flag_highdpi, vec2_i pos, vec2_i size);
void end_scissor();

void begin_drawing();
void end_drawing(Applet *applet);
void clear_screen(tint color_drawn);

void update_viewport(Applet *applet, int w, int h);

// Update Viewport function without the if statement (could produce better performance)
void update_viewport_lite(Applet *applet, int w, int h);

// may only work on desktops
vec2 get_window_scale_dpi(Applet* applet);

#ifdef __cplusplus
}
#endif
