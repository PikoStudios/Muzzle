#ifndef MZ_COLLISION_H
#define MZ_COLLISION_H

#include "../backend.h"
#include <stdio.h>

#define MZ_GET_TIME() glfwGetTime()

/*
* mz_collision v2
* Abstraction Library over sr_resolve.
*/


#ifdef MZ_DEPS_COLLISION
    #define MZ_SR_RESOLVE_IMPLEMENTION
#endif


#include "../../deps/sr_resolve_pks/sr_resolve.h"
typedef sr_ray2 mz_collision_ray2;

#endif // MZ_COLLISION_H