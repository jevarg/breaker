#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

#include "resource_manager.h"
#include "utils.h"

#define SFX_NB 3

static void load_tileset(resource_manager_t *mgr, SDL_Renderer *renderer)
{
    SDL_Surface *loaded_surface = IMG_Load(RES_UI_PATH"/breaker.png");
    mgr->tileset = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (mgr->tileset == NULL)
    {
        print_error("Could not load tileset.");
        print_error(SDL_GetError());
    }
}

static void load_sfx(resource_manager_t *mgr)
{
    mgr->sounds = calloc(SFX_NB, sizeof(Mix_Chunk *));

    mgr->sounds[SFX_BALL_BOUNCE] = Mix_LoadWAV(RES_SFX_PATH"/ball_bounce.wav");
    mgr->sounds[SFX_BRICK_HIT] = Mix_LoadWAV(RES_SFX_PATH"/brick_hit_1.wav");
    mgr->sounds[SFX_BRICK_BREAK] = Mix_LoadWAV(RES_SFX_PATH"/brick_break_1.wav");
}

resource_manager_t *resource_mgr_init(SDL_Renderer *renderer)
{
    resource_manager_t *mgr = calloc(1, sizeof(resource_manager_t));
    if (mgr == NULL)
    {
        print_error("Could not allocate resource manager!");
        return NULL;
    }

    load_tileset(mgr, renderer);
    load_sfx(mgr);

    return mgr;
}

void resource_mgr_destroy(resource_manager_t *mgr)
{
    if (mgr == NULL)
    {
        return;
    }

    SDL_DestroyTexture(mgr->tileset);
    for (size_t i = 0; i < SFX_NB; ++i)
    {
        Mix_FreeChunk(mgr->sounds[i]);
    }
    free(mgr->sounds);
    free(mgr);
}
