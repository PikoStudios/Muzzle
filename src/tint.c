#include "core/tint.h"

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
