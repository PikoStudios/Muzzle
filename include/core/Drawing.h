#pragma once
#include "../backend.h"
#include "tint.h"
#include "Applet.h"

void begin_drawing();
void end_drawing(Applet *applet);
void clear_screen(tint color_drawn);

void update_viewport(Applet *applet, int w, int h);

// Update Viewport function without the if statement (could produce better performance)
void update_viewport_lite(Applet *applet, int w, int h);