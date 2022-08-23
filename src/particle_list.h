#pragma once

#include "particle.h"

typedef struct particle_list_t
{
    particle_t *particle;
    
    particle_list_t *next;
    particle_list_t *prev;
} particle_list_t;

particle_list_t *particle_list_init();
void particle_list_destroy(particle_list_t *);
void particle_list_add(particle_list_t *list, particle_t *particle);
void particle_list_remove(particle_list_t *list, particle_t *particle);
