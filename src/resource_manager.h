#pragma once

#define TILE_WIDTH          16
#define TILE_HEIGHT         TILE_WIDTH

#define RES_ROOT_PATH "../assets"
#define RES_UI_PATH RES_ROOT_PATH"/ui"
#define RES_SFX_PATH RES_ROOT_PATH"/sfx"

#define TILESET_RECT(i) { .w = TILE_WIDTH, .h = TILE_HEIGHT, .x = TILE_WIDTH * i, .y = 0 }

#include <stdbool.h>
#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL2/SDL_mixer.h>
#endif

typedef enum texture_id_t
{
    TEX_BRICK = 0,
    TEX_BRICK_CRACKED_1,
    TEX_BRICK_CRACKED_2,
    TEX_BRICK_CRACKED_3,
    TEX_BRICK_PARTICLES,
    TEX_BAR_LEFT,
    TEX_BAR_BODY,
    TEX_BAR_RIGHT,
    TEX_BALL,
} texture_id_t;

typedef enum sfx_id_t
{
    SFX_BALL_BOUNCE = 0,
    SFX_BRICK_HIT,
    SFX_BRICK_BREAK
} sfx_id_t;

typedef struct resource_manager_t
{
    SDL_Texture *tileset;
    Mix_Chunk **sounds;
} resource_manager_t;

resource_manager_t *resource_mgr_init(SDL_Renderer *renderer);
void resource_mgr_destroy(resource_manager_t *mgr);
