#include "core/tint.h"


tint hex_to_rgb(unsigned int hex[6], unsigned int alpha)
{
    unsigned int r = hex[0] * hex[1];
    unsigned int b = hex[2] * hex[3];
    unsigned int g = hex[4] * hex[5];

    return (tint)
    {
        .r = r,
        .g = g,
        .b = b,
        .a = alpha
    };
}