#include "core/tint.h"

// rgb() IS A DEPRECATED FUNCTION, INSTEAD USE THE RGBA() MACRO
tint rgb(unsigned int red,unsigned int green,unsigned int blue,unsigned int alpha)
{
    return (tint)
    {
        .r = red,
        .g = green,
        .b = blue,
        .a = alpha
    };
}
