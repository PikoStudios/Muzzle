#include "core/Particles.h"

void update_particle(particle* obj)
{
    obj->lifespan -= obj->slasher_amount;
    obj->velocity = (vec2){ obj->velocity.x + obj->acceleration.x, obj->velocity.y + obj->acceleration.y };
    obj->position = (vec2){ obj->position.x + obj->velocity.x, obj->position.y + obj->velocity.y };

    if (obj->lifespan <= 0.0f) obj->dead = MUZZLE_TRUE;
}

void update_particle_delta(particle* obj, float delta)
{
    obj->timer += delta;
    if (obj->timer >= obj->slasher_time)
    {
        obj->lifespan -= obj->slasher_amount;
        obj->timer = 0.0f;
    }

    obj->velocity = (vec2){ obj->velocity.x + obj->acceleration.x, obj->velocity.y + obj->acceleration.y };
    obj->position = (vec2){ obj->position.x + obj->velocity.x, obj->position.y + obj->velocity.y };

    if (obj->lifespan <= 0.0f) obj->dead = MUZZLE_TRUE;
}