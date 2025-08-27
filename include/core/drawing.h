#ifndef MUZZLE_CORE_DRAWING_H
#define MUZZLE_CORE_DRAWING_H

#include "../backend.h"
#include "applet.h"
#include "tint.h"

MZ_API void mz_begin_drawing(mz_applet* applet);
MZ_API void mz_flush_drawing(mz_applet* applet);
MZ_API void mz_flush_shader_passes(mz_applet* applet, mz_boolean retain_shader_passes);
MZ_API void mz_end_drawing(mz_applet* applet);

MZ_API void mz_clear_screen(mz_tint tint);

#endif // MUZZLE_CORE_DRAWING_H
