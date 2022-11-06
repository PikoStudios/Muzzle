#include "core/tint.h"


tint hex_to_rgb(unsigned int hex, unsigned int alpha)
{
    unsigned int r = ((hex >> 16) & 0xFF) / 255;
    unsigned int g = ((hex >> 8) & 0xFF) / 255;
    unsigned int b = ((hex) & 0xFF) / 255;
    
    return (tint)
    {
        .r = r,
        .g = g,
        .b = b,
        .a = alpha
    };
}