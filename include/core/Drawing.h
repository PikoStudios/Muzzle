#pragma once
#include "../backend.h"
#include "tint.h"
#include "vector.h"
#include "Applet.h"
#include "Batcher.h"

extern batcher* _mz_internal_drawing_active_batcher;

#ifdef __cplusplus
extern "C" {
#endif

MZ_API void begin_scissor(Applet* applet, int flag_highdpi, int x, int y, int width, int height);
MZ_API void begin_scissor_vec2(Applet* applet, int flag_highdpi, vec2_i pos, vec2_i size);
MZ_API void end_scissor();

MZ_API void begin_drawing();
MZ_API void end_drawing(Applet *applet);
MZ_API void clear_screen(tint color_drawn);

MZ_API void begin_batcher(batcher* batch);
MZ_API void end_batcher();
MZ_API batcher* get_batcher_scope();

MZ_API void update_viewport(Applet *applet, int w, int h);

// Update Viewport function without the if statement (could produce better performance)
MZ_API void update_viewport_lite(Applet *applet, int w, int h);

// may only work on desktops
MZ_API vec2 get_window_scale_dpi(Applet* applet);

#ifdef __cplusplus
}
#endif
