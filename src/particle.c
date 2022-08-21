#include "particle.h"
#include "utils.h"
#include "brick.h"

particle_t *particle_create(fvec2 pos, vec2 dir, resource_id_t res)
{
    particle_t *particle = malloc(sizeof(particle_t));
    if (particle == NULL)
    {
        print_error("Could not allocate particle");
        return NULL;
    }

    particle->size = (vec2) {
        .x = 16,
        .y = 16
    };
    particle->pos = pos;
    particle->velocity = (fvec2) {1};
    particle->dir = dir;
    
    particle->texture_rect = (SDL_Rect) TILESET_RECT(TEX_BRICK_PARTICLES);
    particle->texture_rect.w = 4;
    particle->texture_rect.h = 4;

    uint8_t particle_offset = 4 * (rand() % 3);
    particle->texture_rect.x += particle_offset;
    // particle->texture_rect.y += particle_offset;

    return particle;
}

void particle_update(particle_t *particle)
{
    particle->pos.x += particle->velocity.x;
    particle->pos.y += particle->velocity.y;

    particle->velocity.x += particle->dir.x;
    particle->velocity.y += particle->dir.y;
}

void particle_draw(particle_t *particle, resource_manager_t *mgr, SDL_Renderer *renderer)
{
     SDL_FRect dstrect = {
         .w = particle->size.x,
         .h = particle->size.y,
         .x = particle->pos.x,
         .y = particle->pos.y
     };

     SDL_RenderCopyF(renderer, mgr->tileset, &particle->texture_rect, &dstrect);
}

void particle_destroy(particle_t **particle)
{
    if (*particle == NULL)
    {
        return;
    }

    free(*particle);
    *particle = NULL;
}
