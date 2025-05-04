#include "../include/dev_pikostudios_muzzle_bridge_Input.h"
#include "core/applet.h"
#include "input/key.h"
#include "input/mouse.h"
#include "../include/common.h"

JNIEXPORT jboolean JNICALL Java_dev_pikostudios_muzzle_bridge_Input_keyPressed(JNIEnv* env, jclass class, jobject applet, jint key)
{
    mz_applet* _applet = get_applet(env, applet);
    return JBOOLEAN(mz_key_pressed(_applet, key));
}

JNIEXPORT jboolean JNICALL Java_dev_pikostudios_muzzle_bridge_Input_keyReleased(JNIEnv* env, jclass class, jobject applet, jint key)
{
    mz_applet* _applet = get_applet(env, applet);
    return JBOOLEAN(mz_key_released(_applet, key));
}

JNIEXPORT jboolean JNICALL Java_dev_pikostudios_muzzle_bridge_Input_mousePressed(JNIEnv* env, jclass class, jobject applet, jint button)
{
    mz_applet* _applet = get_applet(env, applet);
    return JBOOLEAN(mz_mouse_pressed(_applet, button));
}

JNIEXPORT jboolean JNICALL Java_dev_pikostudios_muzzle_bridge_Input_mouseReleased(JNIEnv* env, jclass class, jobject applet, jint button)
{
    mz_applet* _applet = get_applet(env, applet);
    return JBOOLEAN(mz_mouse_released(_applet, button));
}

JNIEXPORT jdouble JNICALL Java_dev_pikostudios_muzzle_bridge_Input_getMouseX(JNIEnv* env, jclass class, jobject applet)
{
    mz_applet* _applet = get_applet(env, applet);
    return (jdouble)(mz_get_mouse_x(_applet));
}

JNIEXPORT jdouble JNICALL Java_dev_pikostudios_muzzle_bridge_Input_getMouseY(JNIEnv* env, jclass class, jobject applet)
{
    mz_applet* _applet = get_applet(env, applet);
    return (jdouble)(mz_get_mouse_y(_applet));
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Input_setCursorState(JNIEnv* env, jclass class, jobject applet, jint state)
{
    mz_applet* _applet = get_applet(env, applet);
    mz_set_cursor_state(_applet, state);
}
