#pragma once

#ifdef _WIN32
    // Include WinAPI if on windows. Required for MultiByteToWideChar
    #include "windows.h"
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
#include <stdlib.h>

#ifdef _cplusplus
    #define __QMF_TYPE extern "C" void
#else
    #define __QMF_TYPE void
#endif


__QMF_TYPE QuitMuzzle(Applet applet);
