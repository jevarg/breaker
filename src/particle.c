#include "particle.h"
#include "utils.h"
#include "brick.h"

#define PARTICLE_TILE_SIZE 4

particle_t *particle_create(fvec2 pos, vec2 dir, texture_id_t res)
{
    particle_t *particle = malloc(sizeof(particle_t));
    if (particle == NULL)
    {
        print_error("Could not allocate particle");
        return NULL;
    }

    particle->size = (vec2) { .x = TILE_WIDTH, .y = TILE_HEIGHT };
    particle->frame_nb = 0;
    particle->pos = pos;
    particle->velocity = (fvec2) {
        (float)((rand() % 100)) / 10,
        (float)((rand() % 100)) / 10
    };

    particle->dir = dir;
    particle->rotation_angle = (double)(rand() % 180) - 90;
    
    particle->texture_rect = (SDL_Rect) TILESET_RECT(res);
    particle->texture_rect.w = PARTICLE_TILE_SIZE;
    particle->texture_rect.h = PARTICLE_TILE_SIZE;

    uint8_t idx = rand() % 8;
    uint8_t particle_offset = PARTICLE_TILE_SIZE * (idx % PARTICLE_TILE_SIZE);
    particle->texture_rect.x += particle_offset;
    particle->texture_rect.y += (idx / PARTICLE_TILE_SIZE) * PARTICLE_TILE_SIZE;

    return particle;
}

void particle_update(particle_t *particle)
{
    particle->pos.x += particle->dir.x * particle->velocity.x;
    particle->pos.y += particle->dir.y * particle->velocity.y;
    particle->rotation_angle += 5;

    particle->velocity.y++;
    ++particle->frame_nb;
}

void particle_draw(particle_t *particle, resource_manager_t *mgr, SDL_Renderer *renderer)
{
     SDL_FRect dstrect = {
         .w = particle->size.x,
         .h = particle->size.y,
         .x = particle->pos.x,
         .y = particle->pos.y
     };

     SDL_RenderCopyExF(renderer, mgr->tileset, &particle->texture_rect, &dstrect, particle->rotation_angle, NULL, SDL_FLIP_NONE);
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
