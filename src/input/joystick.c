#include "input/joystick.h"
#include "core/logging.h"
#include <string.h>

mz_boolean mz_open_joystick(mz_joystick* joystick, uint8_t slot)
{
	if (slot > GLFW_JOYSTICK_LAST || !glfwJoystickPresent(slot))
	{
		return MUZZLE_FALSE;
	}
	
	joystick->slot = slot;
	joystick->is_gamepad = glfwJoystickIsGamepad(slot);
	
	const char* name = joystick->is_gamepad ? glfwGetGamepadName(slot) : glfwGetJoystickName(slot);
	const char* guid = glfwGetJoystickGUID(slot);

	if (name == NULL)
	{
		name = "(Unnamed)";
	}

	if (guid == NULL)
	{
		guid = "(Unknown GUID)";
	}

	MZ_COPY_STRING(joystick->name, sizeof(joystick->name), name);
	MZ_COPY_STRING(joystick->guid, sizeof(joystick->guid), guid);
	
	return MUZZLE_TRUE;
}

mz_boolean mz_joystick_exists(uint8_t slot)
{
	return glfwJoystickPresent(slot);
}

MZ_API mz_boolean mz_query_joystick_state(mz_joystick* joystick, mz_joystick_state* state)
{
	state->axes = glfwGetJoystickAxes(joystick->slot, &state->axes_count);
	state->buttons = (const mz_boolean*)(glfwGetJoystickButtons(joystick->slot, &state->buttons_count));
	state->hats = (const mz_joystick_hat_state*)(glfwGetJoystickHats(joystick->slot, &state->hats_count));

	if (state->axes == NULL || state->buttons == NULL || state->hats == NULL)
	{
		mz_log_status_formatted(LOG_STATUS_ERROR, glfwJoystickPresent(joystick->slot) ? "Failed to query joystick %d state" : "Failed to query joystick %d state, joystick disconnected", joystick->slot);
		memset(state, 0, sizeof(mz_joystick_state));
		return MUZZLE_FALSE;
	}

	return MUZZLE_TRUE;
}

mz_boolean mz_query_gamepad_state(mz_joystick* joystick, mz_gamepad_state* state)
{
	if (!joystick->is_gamepad)
	{
		mz_log_status(LOG_STATUS_ERROR, "Attempted to query gamepad state from non-gamepad joystick");
		return MUZZLE_FALSE;
	}

	int result = glfwGetGamepadState(joystick->slot, (GLFWgamepadstate*)(state));

	if (result == GLFW_FALSE)
	{
		mz_log_status_formatted(LOG_STATUS_ERROR, glfwJoystickPresent(joystick->slot) ? "Failed to query gamepad %d state" : "Failed to query gamepad %d state, gamepad disconnected", joystick->slot);
		return MUZZLE_FALSE;
	}
	
	return MUZZLE_TRUE;
}
