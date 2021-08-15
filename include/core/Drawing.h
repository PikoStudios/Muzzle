#pragma once
#include "../backend.h"
#include "tint.h"
#include "Applet.h"

void begin_drawing();
void end_drawing(Applet *applet);
void clear_screen(tint color_drawn);
void update_viewport(Applet *applet, int w, int h);

