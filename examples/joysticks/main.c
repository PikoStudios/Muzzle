#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define TINTS_COUNT 5

const mz_tint TINTS[TINTS_COUNT] =
{
	TINT_BLUE,
	TINT_ORANGE,
	TINT_WHITE,
	TINT_GRAY,
	TINT_PURPLE
};

void applet_loop(mz_applet* applet)
{
	mz_font font = mz_load_font(applet, "../Roboto.ttf");
	
	mz_joystick joystick = (mz_joystick){0};
	mz_gamepad_state gamepad_state = (mz_gamepad_state){0};
	mz_rectangle rect = (mz_rectangle){applet->width / 2.f, applet->height / 2.f, 100, 100};
	mz_boolean joystick_connected = MUZZLE_FALSE;
	mz_tint tint = TINT_BLUE;
	uint8_t current_tint = 0;
	const char* ui_text = "Waiting for controller to connect";
	mz_boolean show_ui_text = MUZZLE_TRUE;

	mz_boolean right_bumper_pressed = MUZZLE_FALSE;
	mz_boolean left_bumper_pressed = MUZZLE_FALSE;
	mz_boolean right_thumb_pressed = MUZZLE_FALSE;
	mz_boolean left_thumb_pressed = MUZZLE_FALSE;
	
	while (mz_keep_applet(applet))
	{
		if (!joystick_connected && mz_joystick_exists(0))
		{
			if (mz_open_joystick(&joystick, 0))
			{
				printf("Joystick \"%s\" connected on slot 0, is_gamepad=%s\n", joystick.name, joystick.is_gamepad ? "true" : "false");
				joystick_connected = MUZZLE_TRUE;
				ui_text = joystick.name;
			}
		}

		if (joystick_connected)
		{
			if (!mz_joystick_exists(0))
			{
				joystick_connected = MUZZLE_FALSE;
				ui_text = "Waiting for controller to connect";
				show_ui_text = MUZZLE_TRUE;
				printf("Joystick \"%s\" on slot 0 disconnected\n", joystick.name);
			}

			else if (joystick.is_gamepad)
			{
				if (mz_query_gamepad_state(&joystick, &gamepad_state))
				{
					mz_boolean using_stick = MUZZLE_FALSE;
					
					if (gamepad_state.buttons[GAMEPAD_BUTTON_DPAD_RIGHT] || (using_stick = gamepad_state.axes[GAMEPAD_AXIS_LEFT_X] > 0.1f))
					{
						rect.x += 5 * ((using_stick) ? gamepad_state.axes[GAMEPAD_AXIS_LEFT_X] : 1);
					}

					using_stick = MUZZLE_FALSE;

					if (gamepad_state.buttons[GAMEPAD_BUTTON_DPAD_LEFT] || (using_stick = gamepad_state.axes[GAMEPAD_AXIS_LEFT_X] < -0.1f))
					{
						rect.x -= 5 * ((using_stick) ? -gamepad_state.axes[GAMEPAD_AXIS_LEFT_X] : 1);
					}

					using_stick = MUZZLE_FALSE;

					if (gamepad_state.buttons[GAMEPAD_BUTTON_DPAD_DOWN] || (using_stick = gamepad_state.axes[GAMEPAD_AXIS_LEFT_Y] > 0.1f))
					{
						rect.y += 5 * ((using_stick) ? gamepad_state.axes[GAMEPAD_AXIS_LEFT_Y] : 1);
					}

					using_stick = MUZZLE_FALSE;

					if (gamepad_state.buttons[GAMEPAD_BUTTON_DPAD_UP] || (using_stick = gamepad_state.axes[GAMEPAD_AXIS_LEFT_Y] < -0.1f))
					{
						rect.y -= 5 * ((using_stick) ? -gamepad_state.axes[GAMEPAD_AXIS_LEFT_Y] : 1);
					}

					if (gamepad_state.axes[GAMEPAD_AXIS_LEFT_TRIGGER] > 0.0f && rect.width > 5)
					{
						rect.width -= 5;
						rect.height -= 5;
					}
					
					if (gamepad_state.axes[GAMEPAD_AXIS_RIGHT_TRIGGER] > 0.0f)
					{
						rect.width += 5;
						rect.height += 5;
					}

					if (!right_thumb_pressed && gamepad_state.buttons[GAMEPAD_BUTTON_RIGHT_THUMB])
					{
						rect.width = 100;
						rect.height = 100;
						right_thumb_pressed = MUZZLE_TRUE;
					}

					else if (right_thumb_pressed && !gamepad_state.buttons[GAMEPAD_BUTTON_RIGHT_THUMB])
					{
						right_thumb_pressed = MUZZLE_FALSE;
					}

					if (!left_thumb_pressed && gamepad_state.buttons[GAMEPAD_BUTTON_LEFT_THUMB])
					{
						rect.x = applet->width / 2.f;
						rect.y = applet->height / 2.f;
						left_thumb_pressed = MUZZLE_TRUE;
					}

					else if (left_thumb_pressed && !gamepad_state.buttons[GAMEPAD_BUTTON_LEFT_THUMB])
					{
						left_thumb_pressed = MUZZLE_FALSE;
					}

					if (!right_bumper_pressed && gamepad_state.buttons[GAMEPAD_BUTTON_RIGHT_BUMPER])
					{
						current_tint++;

						if (current_tint == TINTS_COUNT)
						{
							current_tint = 0;
						}

						tint = TINTS[current_tint];
						right_bumper_pressed = MUZZLE_TRUE;
					}

					else if (right_bumper_pressed && !gamepad_state.buttons[GAMEPAD_BUTTON_RIGHT_BUMPER])
					{
						right_bumper_pressed = MUZZLE_FALSE;
					}
					
					if (!left_bumper_pressed && gamepad_state.buttons[GAMEPAD_BUTTON_LEFT_BUMPER])
					{
						current_tint--;

						if (current_tint > TINTS_COUNT)
						{
							current_tint = TINTS_COUNT - 1;
						}

						tint = TINTS[current_tint];
						left_bumper_pressed = MUZZLE_TRUE;
					}

					else if (left_bumper_pressed && !gamepad_state.buttons[GAMEPAD_BUTTON_LEFT_BUMPER])
					{
						left_bumper_pressed = MUZZLE_FALSE;
					}

					show_ui_text = !gamepad_state.buttons[GAMEPAD_BUTTON_A];
				}
			}
		}
		
		mz_begin_drawing(applet);
			mz_clear_screen(TINT_BLACK);

			if (joystick_connected)
			{
				mz_draw_rectangle(applet, rect.x - (rect.width / 2.f), rect.y - (rect.height / 2.f), rect.width, rect.height, tint);
			}

			if (show_ui_text)
			{
				mz_draw_text_centered(applet, ui_text, applet->width / 2.f, applet->height / 2.f, 48.f, &font, TINT_WHITE);
			}
			
		mz_end_drawing(applet);
	}

	mz_unload_font(&font);
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [INPUT] - Joysticks", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_TRACK_DELTA_TIME | APPLET_FLAG_VSYNC);
	mz_start_applet(&applet, applet_loop);
	
	mz_terminate_applet(&applet);
	return 0;
}
