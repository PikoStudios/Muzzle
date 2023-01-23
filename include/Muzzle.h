#pragma once

#include "backend.h"

#ifdef MZ_DEPS_COLLISION
    #include "collision/mz_collision.h"
#endif

#ifdef MUZZLE_DEPS
    #define MZ_MATH_IMPLEMENTION
#endif

#ifndef MZ_EXCLUDE_APPLET
    #include "core/Applet.h"
#endif

#ifndef MZ_EXCLUDE_AUDIO
    #include "core/Audio.h"
#endif

#ifndef MUZZLE_SHARED_VARIABLE_ARRAY_SIZE
    #define MUZZLE_SHARED_VARIABLE_ARRAY_SIZE 5
#endif

#include "core/vector.h"
#include "core/Drawing.h"
#include "core/tint.h"
#include "core/Sprite.h"
#include "shapes/Rectangle.h"
#include "shapes/Circle.h"
#include "shapes/Line.h"
#include "core/Text.h"
#include "core/Input.h"
#include "core/Time.h"
//#include "modern_pipeline/Shaders.h"
#include <stdlib.h>

MZ_API void QuitMuzzle(Applet applet);