#pragma once
#include "backend.h"


#ifdef MUZZLE_DEPS
    #define MZ_MATH_IMPLEMENTION
#endif

#ifndef MUZZLE_SHARED_VARIABLE_ARRAY_SIZE
    #define MUZZLE_SHARED_VARIABLE_ARRAY_SIZE 5
#endif

#if defined(MZ_DEPS_COLLISION) || defined(MZ_INCLUDE_COLLISION) // MZ_DEPS_COLLISION is deprecated.
    #include "collision/mz_collision.h"

    #ifdef MZ_DEPS_COLLISION
        #warning "MZ_DEPS_COLLISION is deprecated, instead use MZ_INCLUDE_COLLISION"
    #endif
#endif

/* -- When excluding parts of Muzzle, it is your job to make sure compiliation works -- */
/* -- This also means defining missing types as most parts of Muzzle depend on other parts of Muzzle -- */
/* -- Do not report errors due to excluding parts of Muzzle as bugs -- */


#ifndef MZ_EXCLUDE_CORE
    #ifndef MZ_EXCLUDE_APPLET
        #include "core/Applet.h"
    #endif

    #ifndef MZ_EXCLUDE_AUDIO
        #include "core/Audio.h"
    #endif

    #ifndef MZ_EXCLUDE_VECTOR
        #include "core/vector.h"
    #endif

    #ifndef MZ_EXCLUDE_DRAWING
        #include "core/Drawing.h"
    #endif

    #ifndef MZ_EXCLUDE_TINT
        #include "core/tint.h"
    #endif

    #ifndef MZ_EXCLUDE_SPRITE
        #include "core/Sprite.h"
    #endif

    #ifndef MZ_EXCLUDE_TEXT
        #include "core/Text.h"
    #endif

    #ifndef MZ_EXCLUDE_INPUT
        #include "core/Input.h"
    #endif

    #ifndef MZ_EXCLUDE_TIME
        #include "core/Time.h"
    #endif
#endif

#ifndef MZ_EXCLUDE_SHAPES
    #ifndef MZ_EXCLUDE_RECTANGLE
        #include "shapes/Rectangle.h"
    #endif

    #ifndef MZ_EXCLUDE_CIRCLE
        #include "shapes/Circle.h"
    #endif

    #ifndef MZ_EXCLUDE_LINE
        #include "shapes/Line.h"
    #endif
#endif

#ifdef MZ_INCLUDE_SHADERS
    #warning "WARNING: Shaders are very WIP, do not expect stability"
    #include "modern_pipeline/Shaders.h"
#endif

#include <stdlib.h>
MZ_API void QuitMuzzle(Applet applet);