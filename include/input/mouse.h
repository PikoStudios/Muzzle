#ifndef MUZZLE_INPUT_MOUSE_H
#define MUZZLE_INPUT_MOUSE_H

#include "backend.h"
#include "core/applet.h"
#include "core/vector.h"
typedef enum
{
	MOUSE_BUTTON_LEFT = 0,
	MOUSE_BUTTON_RIGHT = 1,
	MOUSE_BUTTON_MIDDLE = 2
} mz_mouse_button;

MZ_API mz_boolean mz_mouse_pressed(mz_applet* applet, mz_mouse_button button);
MZ_API mz_boolean mz_mouse_released(mz_applet* applet, mz_mouse_button button);

MZ_API mz_vec2_d mz_get_mouse_position(mz_applet* applet);
MZ_API mz_vec2 mz_get_mouse_position_vec2(mz_applet* applet);

MZ_API double mz_get_mouse_x(mz_applet* applet);
MZ_API double mz_get_mouse_y(mz_applet* applet);
MZ_API float mz_get_mouse_xf(mz_applet* applet);
MZ_API float mz_get_mouse_yf(mz_applet* applet);

#endif // MUZZLE_INPUT_MOUSE_H
