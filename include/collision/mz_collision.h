#ifndef MZ_COLLISION_H
#define MZ_COLLISION_H

/*
* Abstraction Library over sr_resolve.
*/


#ifdef MZ_DEPS_COLLISION
    #define MZ_SR_RESOLVE_IMPLEMENTION
#endif


#include "../../deps/sr_resolve_muzzle/sr_resolve.h"

typedef struct collision_manager
{
    double delta;
    double timer;
    double last;
    double now;

    double fps;
} collision_manager;

void update_collision_manager(collision_manager* manager);


#endif // MZ_COLLISION_H