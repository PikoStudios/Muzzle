#include "core/tint.h"


tint hex_to_rgb(unsigned int hex, unsigned int alpha)
{
    unsigned int r = (((hex & 0xF00000) * 16) + (hex & 0x0F0000));
    unsigned int b = (((hex & 0x00F000) * 16) + (hex & 0x000F00));
    unsigned int g = (((hex & 0x0000F0) * 16) + (hex & 0x00000F));

    return (tint)
    {
        .r = r,
        .g = g,
        .b = b,
        .a = alpha
    };
}