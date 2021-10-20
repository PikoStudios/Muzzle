#pragma once

#include <math.h>

// MuzzleMath v2

#define PI  3.14159
#define DEG2RAD     (PI / 180)
#define RAD2DEG     (180 / PI)

float mz_math_clamp(float val, float min, float max);
//{
//    float x = val < min ? min : val;
//    return x > max ? max : x;
//}

float mz_math_lerp(float start, float end, float amount);
//{
//    return start + amount * (end - start);
//}

float mz_math_normalize(float val, float start, float end);
//{
//    return (val - start) / (end - start);
//}

float mz_math_remap(float val, float input_start, float input_end, float output_start, float output_end);
//{
//    return (val - input_start) / (input_end - input_start) * (output_end - output_start) + output_start;
//}

#ifdef MZ_MATH_IMPLEMENTION

float mz_math_clamp(float val, float min, float max)
{
    float x = val < min ? min : val;
    return x > max ? max : x;
}

float mz_math_lerp(float start, float end, float amount)
{
    return start + amount * (end - start);
}

float mz_math_normalize(float val, float start, float end)
{
    return (val - start) / (end - start);
}

float mz_math_remap(float val, float input_start, float input_end, float output_start, float output_end)
{
    return (val - input_start) / (input_end - input_start) * (output_end - output_start) + output_start;
}

#endif // MZ_MATH_IMPLEMENTION
