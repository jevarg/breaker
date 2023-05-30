#pragma once

#include "vec2.h"
#include "resource_manager.h"

typedef struct particle_t
{
    vec2 size;
    fvec2 pos;
    fvec2 velocity;
    vec2 dir;
    double rotation_angle;
    SDL_Rect texture_rect;
    uint32_t frame_nb;
} particle_t;

particle_t *particle_create(fvec2 pos, vec2 dir, texture_id_t res);
void particle_update(particle_t *particle);
void particle_draw(particle_t *particle, resource_manager_t *mgr, SDL_Renderer *renderer);
void particle_destroy(particle_t **particle);
