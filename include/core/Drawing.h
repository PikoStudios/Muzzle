#ifndef MUZZLE_CORE_DRAWING_H
#define MUZZLE_CORE_DRAWING_H

#include "../backend.h"
#include "Applet.h"
#include "tint.h"

MZ_API void begin_drawing(Applet* applet);
MZ_API void end_drawing(Applet* applet);

MZ_API void clear_screen(tint color_drawn);

MZ_API void begin_quad_shader(shader_program program, Applet* applet);
MZ_API void end_quad_shader(Applet* applet);

#endif // MUZZLE_CORE_DRAWING_H