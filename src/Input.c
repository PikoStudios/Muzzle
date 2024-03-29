#include "core/Input.h"

int key_up(Applet *applet, KeyInput key)
{
    if (glfwGetKey(applet->window_handle, key) == GLFW_RELEASE) return 1;
    else return 0;
}
int key_down(Applet *applet, KeyInput key)
{
    if (glfwGetKey(applet->window_handle, key) == GLFW_PRESS) return 1;
    else return 0;
}

int mouse_up(Applet *applet, MouseInput button)
{
    if (glfwGetMouseButton(applet->window_handle, button) == GLFW_RELEASE) return 1;
    else return 0;
}
int mouse_down(Applet *applet, MouseInput button)
{
    if (glfwGetMouseButton(applet->window_handle, button) == GLFW_PRESS) return 1;
    else return 0;
}

vec2_d get_mouse_posititon(Applet* applet)
{
    vec2_d buf;
    glfwGetCursorPos(applet->window_handle, &buf.x, &buf.y);
    return buf;
}

double get_mouse_x(Applet* applet)
{
    return get_mouse_posititon(applet).x;
}

double get_mouse_y(Applet* applet)
{
    return get_mouse_posititon(applet).y;
}

vec2 get_mouse_position_vec2(Applet* applet)
{
    vec2_d buf;
    glfwGetCursorPos(applet->window_handle, &buf.x, &buf.y);
    return (vec2) {(float)(buf.x), (float)(buf.y)};
}

float get_mouse_xf(Applet* applet)
{
    return get_mouse_position_vec2(applet).x;
}

float get_mouse_yf(Applet* applet)
{
    return get_mouse_position_vec2(applet).y;
}

int is_gamepad_online(int pad)
{
    return glfwJoystickPresent(pad);
}

const char* get_gamepad_name(int pad)
{
    return glfwGetGamepadName(pad);
}

void get_gamepad_state(gamepad* pad)
{
    int buf = glfwGetGamepadState(pad->pad, &pad->state);
    if (!buf)
    {
        char error[254];
        sprintf(error, "Gamepad %d is not connected and/or operating. TIP: Use 'is_gamepad_online' to check the avaliability of gamepads", pad->pad);
        log_status(STATUS_ERROR, error);
    }
}