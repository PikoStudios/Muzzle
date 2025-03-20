#include "../include/dev_pikostudios_muzzle_bridge_Key.h"
#include "core/applet.h"
#include "input/key.h"
#include "../include/common.h"

JNIEXPORT jboolean JNICALL Java_dev_pikostudios_muzzle_bridge_Key_keyPressed(JNIEnv* env, jclass class, jobject applet, jint key)
{
    mz_applet* _applet = get_applet(env, applet);
    return JBOOLEAN(mz_key_pressed(_applet, key));
}

JNIEXPORT jboolean JNICALL Java_dev_pikostudios_muzzle_bridge_Key_keyReleased(JNIEnv* env, jclass class, jobject applet, jint key)
{
    mz_applet* _applet = get_applet(env, applet);
    return JBOOLEAN(mz_key_released(_applet, key));
}
