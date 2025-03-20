#include "../include/dev_pikostudios_muzzle_bridge_Rectangle.h"
#include "core/applet.h"
#include "core/tint.h"
#include "primitives/rectangle.h"
#include "../include/common.h"

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Rectangle_draw(JNIEnv* env, jclass class, jobject applet, jfloat x, jfloat y, jfloat width, jfloat height, jobject tint)
{
    mz_applet* _applet = get_applet(env, applet);

    mz_tint _tint = get_tint(env, tint);

    mz_draw_rectangle(_applet, (float)(x), (float)(y), (float)(width), (float)(height), _tint);
}
