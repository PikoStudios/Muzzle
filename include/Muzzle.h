#pragma once

#include "backend.h"

#ifdef MZ_DEPS_COLLISION
    #include "collision/mz_collision.h"
#endif

#ifdef MUZZLE_DEPS
    #define MZ_MATH_IMPLEMENTION
#endif

#include "core/Applet.h"

#ifndef MZ_EXCLUDE_AUDIO
    #include "core/Audio.h"
#endif

#ifndef MUZZLE_SHARED_VARIABLE_ARRAY_SIZE
    #define MUZZLE_SHARED_VARIABLE_ARRAY_SIZE 5
#endif

#define MUZZLE_INTERNAL_DEBUG_ASSERT_HANDLE_FAILURE(x) fprintf(stderr, "Muzzle Assert Failure: %s", x); *(int*)0=0;


#define MUZZLE_DEBUG_ASSERT(x, message) ((x) ? (void)(0) : MUZZLE_INTERNAL_DEBUG_ASSERT_HANDLE_FAILURE(message))


#include "MuzzleGL.h"
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
#include <stdlib.h>

MZ_API void QuitMuzzle(Applet applet);