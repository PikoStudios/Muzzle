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

    float lifespan;
    int dead;

    float slasher_amount; // How much to slash off the lifespan every update
};

typedef struct _mz_particle particle;

void update_particle(particle* obj);