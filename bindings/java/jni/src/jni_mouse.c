#include "../include/dev_pikostudios_muzzle_bridge_Mouse.h"
#include "core/applet.h"
#include "input/mouse.h"
#include "../include/common.h"

JNIEXPORT jboolean JNICALL Java_dev_pikostudios_muzzle_bridge_Mouse_mousePressed(JNIEnv* env, jclass class, jobject applet, jint button)
{
    mz_applet* _applet = get_applet(env, applet);
    return JBOOLEAN(mz_mouse_pressed(_applet, button));
}

JNIEXPORT jboolean JNICALL Java_dev_pikostudios_muzzle_bridge_Mouse_mouseReleased(JNIEnv* env, jclass class, jobject applet, jint button)
{
    mz_applet* _applet = get_applet(env, applet);
    return JBOOLEAN(mz_mouse_released(_applet, button));
}

JNIEXPORT jdouble JNICALL Java_dev_pikostudios_muzzle_bridge_Mouse_getMouseX(JNIEnv* env, jclass class, jobject applet)
{
    mz_applet* _applet = get_applet(env, applet);
    return (jdouble)(mz_get_mouse_x(_applet));
}

JNIEXPORT jdouble JNICALL Java_dev_pikostudios_muzzle_bridge_Mouse_getMouseY(JNIEnv* env, jclass class, jobject applet)
{
    mz_applet* _applet = get_applet(env, applet);
    return (jdouble)(mz_get_mouse_y(_applet));
}
