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
    
    int updates;
} collision_manager;

typedef sr_ray2 ray2;

void begin_collision_manager(collision_manager* manager);
void end_collision_manager(collision_manager* manager);

void move_and_slide(rectangle *recs, int recs_length, vec2 hitbox, vec2 *velocity, vec2 *pos, collision_manager* manager);

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
        printf("Collision Updates: %f, Collision FPS Lock: %f\r", manager->updates, manager->fps);
#endif

        manager->updates = 0;
    }
}

void move_and_slide(rectangle *recs, int recs_length, vec2 hitbox, vec2 *velocity, vec2 *pos, collision_manager* manager)
{
    while (manager->delta >= 1.0)
    {
        sr_move_and_slide(recs, recs_length, hitbox, velocity, pos, manager->delta);
        manager->updates++;
        manager->delta--;
    }
}

#endif


#endif // MZ_COLLISION_H