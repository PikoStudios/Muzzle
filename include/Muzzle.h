#pragma once

#ifdef _WIN32
    // Include WinAPI if on windows. Required for MultiByteToWideChar
    #include "windows.h"
#endif

#ifdef MZ_DEPS_COLLISION
    #include "collision/mz_collision.h"
#endif

#ifdef MUZZLE_DEPS
    #define MZ_MATH_IMPLEMENTION
#endif

#include "core/Applet.h"
#include "core/vector.h"
#include "core/Drawing.h"
#include "core/tint.h"
#include "core/Sprite.h"
#include "shapes/Rectangle.h"
#include "shapes/Circle.h"
#include "core/Text.h"
#include "core/Input.h"
#include "core/Time.h"
#include <stdlib.h>

void QuitMuzzle(Applet applet);
