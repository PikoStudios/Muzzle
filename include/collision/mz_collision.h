#ifndef MZ_COLLISION_H
#define MZ_COLLISION_H

#include "../backend.h"
#include <stdio.h>

#define MZ_GET_TIME() glfwGetTime()

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

    int frames;
    int updates;
} collision_manager;

void begin_collision_manager(collision_manager* manager);
void end_collision_manager(collision_manager* manager);


#define MZ_DEPS_COLLISION

#ifdef MZ_DEPS_COLLISION

void begin_collision_manager(collision_manager* manager)
{
    manager->now = glfwGetTime();
    manager->delta += (manager->now - manager->last) / manager->fps;
    manager->last = manager->now;
}

void end_collision_manager(collision_manager* manager)
{
    if (glfwGetTime() - manager->timer > 1.0)
    {
        manager->timer++;

#ifdef MZ_COLLISION_VERBOSE
        fflush(stdout);
        printf("Collision FPS: %f, Collision Updates: %f, Collision FPS Lock: %f\r", manager->frames, manager->updates, manager->fps);
#endif

        manager->updates = 0;
        manager->frames = 0;
    }
}

#endif


#endif // MZ_COLLISION_H