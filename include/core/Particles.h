#pragma once
#include "../backend.h"
#include "tint.h"

#include "../shapes/Rectangle.h"
#include "../shapes/Circle.h"
#include "Sprite.h"

struct _mz_particle
{
    tint color_drawn;
    float lifespan;

    float timer;
    void* draw;
};

typedef struct _mz_particle particle;

struct _mz_particle_descriptor
{
    tint color_drawn;
    float lifespan;

    void (*update)(particle*);
    void (*draw)(particle*);

    void* copier;

    size_t count;
    particle** array;
};

typedef struct _mz_particle_descriptor particle_descriptor;

void spawn_particle(particle_descriptor *descriptor);
void update_particle(particle_descriptor *descriptor);
void draw_particle(particle_descriptor *descriptor);