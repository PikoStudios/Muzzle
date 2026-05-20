#ifndef MUZZLE_INPUT_JOYSTICK_H
#define MUZZLE_INPUT_JOYSTICK_H

#include "../backend.h"
#include <stdint.h>

typedef struct mz_joystick
{
	uint8_t slot;
	mz_boolean is_gamepad;
	char name[MUZZLE_INPUT_MAX_JOYSTICK_NAME_LENGTH + 1];
	char guid[MUZZLE_INPUT_JOYSTICK_GUID_LENGTH + 1];
} mz_joystick;

typedef enum
{
	JOYSTICK_HAT_STATE_CENTERED = 0,
	JOYSTICK_HAT_STATE_UP = 1,
	JOYSTICK_HAT_STATE_RIGHT = 2,
	JOYSTICK_HAT_STATE_DOWN = 4,
	JOYSTICK_HAT_STATE_LEFT = 8,
	JOYSTICK_HAT_STATE_RIGHT_UP = JOYSTICK_HAT_STATE_RIGHT | JOYSTICK_HAT_STATE_UP,
	JOYSTICK_HAT_STATE_RIGHT_DOWN = JOYSTICK_HAT_STATE_RIGHT | JOYSTICK_HAT_STATE_DOWN,
	JOYSTICK_HAT_STATE_LEFT_UP = JOYSTICK_HAT_STATE_LEFT | JOYSTICK_HAT_STATE_UP,
	JOYSTICK_HAT_STATE_LEFT_DOWN = JOYSTICK_HAT_STATE_LEFT | JOYSTICK_HAT_STATE_DOWN,
} mz_joystick_hat_state;

typedef enum
{
	GAMEPAD_BUTTON_A = 0,
	GAMEPAD_BUTTON_B = 1,
	GAMEPAD_BUTTON_X = 2,
	GAMEPAD_BUTTON_Y = 3,
	GAMEPAD_BUTTON_LEFT_BUMPER = 4,
	GAMEPAD_BUTTON_RIGHT_BUMPER = 5,
	GAMEPAD_BUTTON_BACK = 6,
	GAMEPAD_BUTTON_START = 7,
	GAMEPAD_BUTTON_GUIDE = 8,
	GAMEPAD_BUTTON_LEFT_THUMB = 9,
	GAMEPAD_BUTTON_RIGHT_THUMB = 10,
	GAMEPAD_BUTTON_DPAD_UP = 11,
	GAMEPAD_BUTTON_DPAD_RIGHT = 12,
	GAMEPAD_BUTTON_DPAD_DOWN = 13,
	GAMEPAD_BUTTON_DPAD_LEFT = 14,
	GAMEPAD_BUTTON_CROSS = GAMEPAD_BUTTON_A,
	GAMEPAD_BUTTON_CRICLE = GAMEPAD_BUTTON_B,
	GAMEPAD_BUTTON_SQUARE = GAMEPAD_BUTTON_X,
	GAMEPAD_BUTTON_TRIANGLE = GAMEPAD_BUTTON_Y
} mz_gamepad_button;

typedef enum
{
	GAMEPAD_AXIS_LEFT_X = 0,
	GAMEPAD_AXIS_LEFT_Y = 1,
	GAMEPAD_AXIS_RIGHT_X = 2,
	GAMEPAD_AXIS_RIGHT_Y = 3,
	GAMEPAD_AXIS_LEFT_TRIGGER = 4,
	GAMEPAD_AXIS_RIGHT_TRIGGER = 5
} mz_gamepad_axis;

typedef struct mz_joystick_state
{
	const float* axes;
	const mz_boolean* buttons;
	const mz_joystick_hat_state* hats;
	int hats_count;
	int axes_count;
	int buttons_count;
} mz_joystick_state;

typedef struct mz_gamepad_state
{
	mz_boolean buttons[15]; // MUZZLE_FALSE => not pressed, MUZZLE_TRUE => pressed
	float axes[6]; // -1.0 to 1.0 inclusive
} mz_gamepad_state;

_Static_assert(sizeof(mz_gamepad_state) == sizeof(GLFWgamepadstate), "Gamepad state size mismatch");
_Static_assert(offsetof(mz_gamepad_state, buttons) == offsetof(GLFWgamepadstate, buttons), "Gamepad state buttons field offset mismatch");
_Static_assert(offsetof(mz_gamepad_state, axes) == offsetof(GLFWgamepadstate, axes), "Gamepad state axes field offset mismatch");
_Static_assert(sizeof(((mz_gamepad_state*)(NULL))->buttons) == sizeof(((GLFWgamepadstate*)(NULL))->buttons), "Gamepad state buttons size mismatch");
_Static_assert(sizeof(((mz_gamepad_state*)(NULL))->axes) == sizeof(((GLFWgamepadstate*)(NULL))->axes), "Gamepad state axes size mismatch");

typedef enum
{
	JOYSTICK_QUERY_ERROR_DOES_NOT_EXIST = 0
} mz_joystick_query_error;

MZ_API mz_boolean mz_init_joystick(mz_joystick* joystick, uint8_t slot);
MZ_API mz_boolean mz_joystick_exists(uint8_t slot);
MZ_API mz_boolean mz_query_joystick_state(mz_joystick* joystick, mz_joystick_state* state);
MZ_API mz_boolean mz_query_gamepad_state(mz_joystick* joystick, mz_gamepad_state* state);

#endif // MUZZLE_INPUT_JOYSTICK_H
