#ifndef MZ_COLLISION_H
#define MZ_COLLISION_H

#include "../backend.h"
#include "../core/vector.h"

#include <stdio.h>

#define MZ_GET_TIME() glfwGetTime()

/*
* mz_collision v2.1
* Abstraction Library over sr_resolve.
*/


#ifdef MZ_DEPS_COLLISION || MZ_INCLUDE_ALL_EXTRAS
    #define MZ_SR_RESOLVE_IMPLEMENTION
#endif


#include "../../deps/sr_resolve/sr_resolve.h"
typedef sr_ray2 mz_collision_ray2;


MZ_API float mz_collision_length(vec2 v);

MZ_API vec2 mz_collision_scale(vec2 v, float scale);
MZ_API vec2 mz_collision_divide(vec2 v1, vec2 v2);
MZ_API vec2 mz_collision_multiply(vec2 v1, vec2 v2);
MZ_API vec2 mz_collision_normalize(vec2 v);


MZ_API vec2 mz_collision_sub(vec2 v1, vec2 v2);
MZ_API vec2 mz_collision_add(vec2 v1, vec2 v2);

#ifdef MZ_DEPS_COLLISION

// Get the length of a vector
float mz_collision_length(vec2 v) {
	float result = sqrtf((v.x*v.x) + (v.y*v.y));
  	return result;
}

// Scale a vector by a given float value
vec2 mz_collision_scale(vec2 v, float scale) {
  	return (vec2){ v.x*scale, v.y*scale };
}

// Divide two vectors
vec2 mz_collision_divide(vec2 v1, vec2 v2) {
  	return (vec2){ v1.x/v2.x, v1.y/v2.y };
}

// Multiply two vectors
vec2 mz_collision_multiply(vec2 v1, vec2 v2) {
  	return (vec2){ v1.x*v2.x, v1.y*v2.y };
}

// Normalize a vector
vec2 mz_collision_normalize(vec2 v) {
  	return mz_collision_scale(v, 1 / mz_collision_length(v));
}

// Substract two vectors
vec2 mz_collision_sub(vec2 v1, vec2 v2) {
  	return (vec2){ v1.x - v2.x, v1.y - v2.y };
}

// Add two vectors
vec2 mz_collision_add(vec2 v1, vec2 v2) {
  	return (vec2){ v1.x + v2.x, v1.y + v2.y };
}

#endif // MZ_DEPS_COLLISION

#endif // MZ_COLLISION_H