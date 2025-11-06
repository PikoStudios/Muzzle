#include "input/input_manager.h"
#include "backend.h"
#include "input/key.h"
#include <stdint.h>

static const uint16_t KEYCODE_ORDINAL_LUT[KEY_MAX_VALUE + 1] =
{
	[KEY_NONE] = 0,
    [KEY_SPACE] = 1,
    [KEY_APOSTROPHE] = 2,
    [KEY_COMMA] = 3,
    [KEY_MINUS] = 4,
    [KEY_PERIOD] = 5,
    [KEY_SLASH] = 6,
    [KEY_ZERO] = 7,
    [KEY_ONE] = 8,
    [KEY_TWO] = 9,
    [KEY_THREE] = 10,
    [KEY_FOUR] = 11,
    [KEY_FIVE] = 12,
    [KEY_SIX] = 13,
    [KEY_SEVEN] = 14,
    [KEY_EIGHT] = 15,
    [KEY_NINE] = 16,
    [KEY_SEMICOLON] = 17,
    [KEY_EQUAL] = 18,
    [KEY_A] = 19,
    [KEY_B] = 20,
    [KEY_C] = 21,
    [KEY_D] = 22,
    [KEY_E] = 23,
    [KEY_F] = 24,
    [KEY_G] = 25,
    [KEY_H] = 26,
    [KEY_I] = 27,
    [KEY_J] = 28,
    [KEY_K] = 29,
    [KEY_L] = 30,
    [KEY_M] = 31,
    [KEY_N] = 32,
    [KEY_O] = 33,
    [KEY_P] = 34,
    [KEY_Q] = 35,
    [KEY_R] = 36,
    [KEY_S] = 37,
    [KEY_T] = 38,
    [KEY_U] = 39,
    [KEY_V] = 40,
    [KEY_W] = 41,
    [KEY_X] = 42,
    [KEY_Y] = 43,
    [KEY_Z] = 44,
    [KEY_LEFT_BRACKET] = 45,
    [KEY_BACKSLASH] = 46,
    [KEY_RIGHT_BRACKET] = 47,
    [KEY_GRAVE] = 48,
    [KEY_ESCAPE] = 49,
    [KEY_ENTER] = 50,
    [KEY_TAB] = 51,
    [KEY_BACKSPACE] = 52,
    [KEY_INSERT] = 53,
    [KEY_DELETE] = 54,
    [KEY_RIGHT] = 55,
    [KEY_LEFT] = 56,
    [KEY_DOWN] = 57,
    [KEY_UP] = 58,
    [KEY_PAGE_UP] = 59,
    [KEY_PAGE_DOWN] = 60,
    [KEY_HOME] = 61,
    [KEY_END] = 62,
    [KEY_CAPS_LOCK] = 63,
    [KEY_SCROLL_LOCK] = 64,
    [KEY_NUM_LOCK] = 65,
    [KEY_PRINT_SCREEN] = 66,
    [KEY_PAUSE] = 67,
    [KEY_F1] = 68,
    [KEY_F2] = 69,
    [KEY_F3] = 70,
    [KEY_F4] = 71,
    [KEY_F5] = 72,
    [KEY_F6] = 73,
    [KEY_F7] = 74,
    [KEY_F8] = 75,
    [KEY_F9] = 76,
    [KEY_F10] = 77,
    [KEY_F11] = 78,
    [KEY_F12] = 79,
    [KEY_LEFT_SHIFT] = 80,
    [KEY_LEFT_CONTROL] = 81,
    [KEY_LEFT_ALT] = 82,
    [KEY_LEFT_SUPER] = 83,
    [KEY_RIGHT_SHIFT] = 84,
    [KEY_RIGHT_CONTROL] = 85,
    [KEY_RIGHT_ALT] = 86,
    [KEY_RIGHT_SUPER] = 87,
    [KEY_KB_MENU] = 88,
};

mz_boolean mz_key_pressed_once(mz_applet* applet, mz_input_manager* input, mz_key key)
{
	MZ_TRACK_FUNCTION();
	MZ_ASSERT_DETAILED(key >= 0 && key <= KEY_MAX_VALUE, "Invalid key value");

	if (!input->keys[KEYCODE_ORDINAL_LUT[key]] && mz_key_pressed(applet, key))
	{
		input->keys[KEYCODE_ORDINAL_LUT[key]] = MUZZLE_TRUE;
		return MUZZLE_TRUE;
	}

	if (input->keys[KEYCODE_ORDINAL_LUT[key]] && mz_key_released(applet, key))
	{
		input->keys[KEYCODE_ORDINAL_LUT[key]] = MUZZLE_FALSE;
	}

	return MUZZLE_FALSE;
}

mz_boolean mz_mouse_pressed_once(mz_applet* applet, mz_input_manager* input, mz_mouse_button button)
{
	MZ_ASSERT_DETAILED(button >= 0 && button < MOUSE_BUTTON_COUNT, "Invalid button value");
	
	if (!input->mouse_buttons[button] && mz_mouse_pressed(applet, button))
	{
		input->mouse_buttons[button] = MUZZLE_TRUE;
		return MUZZLE_TRUE;
	}

	if (input->mouse_buttons[button] && mz_mouse_released(applet, button))
	{
		input->mouse_buttons[button] = MUZZLE_FALSE;
	}

	return MUZZLE_FALSE;
}
