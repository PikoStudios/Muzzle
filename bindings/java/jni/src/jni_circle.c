#include "../include/dev_pikostudios_muzzle_bridge_Circle.h"
#include "../include/common.h"
#include "primitives/circle.h"
#include "jni.h"

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Circle_draw(JNIEnv* env, jclass class, jobject applet, jfloat x, jfloat y, jfloat radius, jobject tint)
{
    mz_applet* _applet = get_applet(env, applet);
    mz_tint _tint = get_tint(env, tint);

    mz_draw_circle(_applet, x, y, radius, _tint);
}
