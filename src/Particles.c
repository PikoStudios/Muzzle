#include "core/Particles.h"

void spawn_particle(particle_descriptor *descriptor)
{
    descriptor->array[descriptor->count - 1]->draw = descriptor->copier;
    descriptor->array[descriptor->count - 1]->lifespan = descriptor->lifespan;

    descriptor->array[descriptor->count - 1]->color_drawn = descriptor->color_drawn;
    descriptor->array[descriptor->count - 1]->timer = 0.f;
}

void update_particle(particle_descriptor *descriptor)
{
    for (int i = 0; i < descriptor->count; i++)
    {
        if (descriptor->array[i]->timer >= descriptor->array[i]->lifespan) descriptor->array[i] = NULL;
        else descriptor->update(descriptor->array[i]);
    }   
}

void draw_particle(particle_descriptor *descriptor)
{
    for (int i = 0; i < descriptor->count; i++)
    {
        if (!descriptor->array[i] == NULL) descriptor->draw(descriptor->array[i]);
        else return;
    }
}