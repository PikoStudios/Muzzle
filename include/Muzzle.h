#pragma once

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

static void* __muzzle_shared_variable_array[MUZZLE_SHARED_VARIABLE_ARRAY_SIZE];

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

void create_shared_variable(void* variable, int index);
void remove_shared_variable(int index);
void* get_shared_variable(int index);