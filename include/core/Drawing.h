#pragma once
#include "../backend.h"
#include "tint.h"
#include "Applet.h"

#ifdef _cplusplus
    extern "C" {
#endif


void begin_drawing();
void end_drawing(Applet *applet);
void clear_screen(tint color_drawn);
void update_viewport(Applet *applet, int w, int h);


#ifdef _cplusplus
}
#endif