#include "../include/dev_pikostudios_muzzle_bridge_Drawing.h"
#include "core/drawing.h"
#include "core/applet.h"
#include "../include/common.h"

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Drawing_startDrawing(JNIEnv* env, jclass class, jobject applet)
{
    mz_applet* _applet = get_applet(env, applet);
    mz_begin_drawing(_applet);
}

JNIEXPORT void JNICALL Java_dev_pikostudios_muzzle_bridge_Drawing_endDrawing(JNIEnv* env, jclass class, jobject applet)
{
    mz_applet* _applet = get_applet(env, applet);
    mz_end_drawing(_applet);
}
