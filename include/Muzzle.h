#ifndef MUZZLE_H
#define MUZZLE_H

#ifdef MUZZLE_DEBUG_BUILD
    #include "backend.h"
    char* __mz_debug_current_function_name = "unknown";
#endif

#include "core/logging.h"
#include "core/applet.h"
#include "core/shader.h"
#include "core/vector.h"
#include "core/drawing.h"

#include "primitives/rectangle.h"
#include "primitives/sprite.h"
#include "primitives/circle.h"
#include "primitives/text.h"

#include "input/key.h"
#include "input/mouse.h"

#endif // MUZZLE_H
