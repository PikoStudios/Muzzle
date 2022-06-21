#pragma once
#include "../backend.h"
#include "vector.h"
#include "tint.h"

// Low-Level Barebones Particle System

struct _mz_particle
{
    vec2 position;
    vec2 velocity;
    vec2 acceleration;

    float lifespan; // recommended default is 255
    int dead; // set to 0 or MUZZLE_FALSE

    float timer; // set to 0.0f, If not using `update_particle_delta`, ignore this.
    float slasher_amount; // How much to slash off the lifespan every update
    float slasher_time; // If not using `update_particle_delta`, ignore this.
};

typedef struct _mz_particle particle;

void update_particle(particle* obj);
void update_particle_delta(particle* obj, float delta); // Will decrease lifespan every second