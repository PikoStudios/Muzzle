#pragma once

#ifdef _cplusplus
    extern "C" {
#endif

typedef struct vec2
{
    float x;
    float y;
} vec2;

typedef struct vec3
{
    float x;
    float y;
    float z;
} vec3;

// Vector2 with doubles
typedef struct vec2_d
{
    double x;
    double y;
} vec2_d;

// Vector3 with doubles
typedef struct vec3_d
{
    double x;
    double y;
    double z;
} vec3_d;


#ifdef _cplusplus
}
#endif