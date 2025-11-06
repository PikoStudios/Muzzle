#ifndef MUZZLE_INPUT_MANAGER_H
#define MUZZLE_INPUT_MANAGER_H

#include "../backend.h"
#include "mouse.h"
#include "key.h"

typedef struct mz_input_manager
{
	mz_boolean keys[KEY_COUNT];
	mz_boolean mouse_buttons[MOUSE_BUTTON_COUNT];
} mz_input_manager;

mz_boolean mz_key_pressed_once(mz_applet* applet, mz_input_manager* input, mz_key key);
mz_boolean mz_mouse_pressed_once(mz_applet* applet, mz_input_manager* input, mz_mouse_button button);

#endif // MUZZLE_INPUT_MANAGER_H
