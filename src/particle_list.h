#pragma once

#include "particle.h"

typedef struct particle_list_node_t particle_list_node_t;

struct particle_list_node_t
{
    particle_t *particle;
    
    particle_list_node_t *next;
    particle_list_node_t *prev;
};

particle_list_node_t *particle_list_init();
void particle_list_destroy(particle_list_node_t *node);
void particle_list_add(particle_list_node_t *node, particle_t *particle);
void particle_list_remove(particle_list_node_t *node);
void particle_list_find_and_remove(particle_list_node_t *root_node, particle_t *particle);
