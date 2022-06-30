#pragma once

// MuzzleMath v2.3

/*
*   CHANGE LOG (2.3)
*   - Added MZ_MATH_STANDALONE macro
*   - Added quadratic formula functions
*   - Added true sqroot functions
*/

#include <math.h>

#ifndef MZ_MATH_STANDALONE
    #include "core/vector.h"
    #include "backend.h"

    #define MZ_MATH_VECTOR2 vec2
    #define MZ_MATH_VECTOR2_DOUBLE vec2_d
#else
    typedef struct mz_math_vec2
    {
        float x;
        float y;
    } mz_math_vec2; // not named vec2 to avoid name conflicts

    typedef struct mz_math_vec2_d
    {
        double x;
        double y;
    } mz_math_vec2_d; // not named vec2_d to avoid name conflicts

    #define MZ_MATH_VECTOR2 mz_math_vec2
    #define MZ_MATH_VECTOR2_DOUBLE mz_math_vec2_d

    #define MZ_API
#endif // MZ_MATH_STANDALONE

#define PI  3.14159
#define DEG2RAD     (PI / 180)
#define RAD2DEG     (180 / PI)

MZ_API float mz_math_clamp(float val, float min, float max);
MZ_API float mz_math_clamp_then_boost(float val, float min, float max, float booster);
MZ_API float mz_math_lerp(float start, float end, float amount);

MZ_API float mz_math_normalize(float val, float start, float end);
MZ_API float mz_math_remap(float val, float input_start, float input_end, float output_start, float output_end);

//// Not allocated. No need to free()
//float** mz_math_quadratic_formula_array(float a, float b, float c);
//MZ_MATH_VECTOR2 mz_math_quadratic_formula_vec2(float a, float b, float c); // MZ_MATH_VECTOR2 is either vec2 or mz_math_vec2. both are the same.
//
//// Not allocated. No need to free()
//double** mz_math_quadratic_formula_array_double(double a, double b, double c);
//MZ_MATH_VECTOR2_DOUBLE mz_math_quadratic_formula_vec2_d(double a, double b, double c);
//
//double** mz_math_true_sqroot(double val);
//MZ_MATH_VECTOR2_DOUBLE mz_math_true_sqroot_vec2_d(double val);
//
//float** mz_math_true_sqroot_float(float val);
//MZ_MATH_VECTOR2 mz_math_true_sqroot_vec2(float val);

#ifdef MZ_MATH_IMPLEMENTION

float mz_math_clamp(float val, float min, float max)
{
    float x = val < min ? min : val;
    return x > max ? max : x;
}

float mz_math_clamp_then_boost(float val, float min, float max, float booster)
{
    float x = val < min ? min + booster : val;
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

//float** mz_math_quadratic_formula_array(float a, float b, float c)
//{
//    float** res;
//    float sqroot_val = sqrt((b*b) - (4 * a * c));
//
//    *res[0] = (-b + sqroot_val) / (2 * a);
//    *res[1] = (-b - sqroot_val) / (2 * a);
//
//    return res;
//}
//
//MZ_MATH_VECTOR2 mz_math_quadratic_formula_vec2(float a, float b, float c)
//{
//    float** res = mz_math_quadratic_formula_array(a,b,c);
//
//    return (MZ_MATH_VECTOR2){.x = *res[0], .y = *res[1]};
//}
//
//double** mz_math_quadratic_formula_array_double(double a, double b, double c)
//{
//    double** res;
//    double sqroot_val = sqrt((b*b) - (4 * a * c));
//
//    *res[0] = (-b + sqroot_val) / (2 * a);
//    *res[1] = (-b - sqroot_val) / (2 * a);
//
//    return res;   
//}
//
//MZ_MATH_VECTOR2_DOUBLE mz_math_quadratic_formula_vec2_d(double a, double b, double c)
//{
//    double** res = mz_math_quadratic_formula_array_double(a,b,c);
//
//    return (MZ_MATH_VECTOR2_DOUBLE){.x = *res[0], .y = *res[1]};
//}
//
//double** mz_math_true_sqroot(double val)
//{
//    double sq = sqrt(val);
//    double** res{sq, -sq};
//
//    return res;
//}
//
//MZ_MATH_VECTOR2_DOUBLE mz_math_true_sqroot_vec2_d(double val)
//{
//    double** res = mz_math_true_sqroot(val);
//
//    return (MZ_MATH_VECTOR2_DOUBLE){.x = *res[0], .y = *res[1]};
//}
//
//float** mz_math_true_sqroot_float(float val)
//{
//    float sq = sqrtf(val);
//    float** res = {sq, -sq};
//
//    return res;
//}
//
//MZ_MATH_VECTOR2 mz_math_true_sqroot_vec2(float val)
//{
//    float** res = mz_math_true_sqroot_float(val);
//
//    return (MZ_MATH_VECTOR2){.x = *res[0], .y = *res[1]};
//}

#endif // MZ_MATH_IMPLEMENTION