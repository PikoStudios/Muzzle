#include "core/Particles.h"

void update_particle(particle* obj)
{
    obj->velocity = (vec2){ obj->velocity.x + obj->acceleration.x, obj->velocity.y + obj->acceleration.y };
    obj->position = (vec2){ obj->position.x + obj->velocity.x, obj->position.y + obj->velocity.y };
    obj->lifespan -= obj->slasher_amount;

    if (obj->lifespan <= 0.0f) obj->dead = MUZZLE_TRUE;
}