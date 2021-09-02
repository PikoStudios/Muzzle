#include "core/tint.h"

tint rgb(unsigned int red,unsigned int green,unsigned int blue,unsigned int alpha)
{
#ifndef MZ_SUPPRESS_RGB_DEPRECATION_WARNINGS || MZ_SUPPRESS_DEPRECATION_WARNINGS
    #warning rgb() IS A DEPRECATED FUNCTION, INSTEAD USE THE RGBA() MACRO, TO SUPPRESS RGB DEPRECATION WARNINGS DEFINE MZ_SUPPRESS_RGB_DEPRECATION_WARNINGS
    #warning To suppress deprecation warnings define MZ_SUPPRESS_DEPRECATION_WARNINGS
#endif

    return (tint)
    {
        .r = red,
        .g = green,
        .b = blue,
        .a = alpha
    };
}
