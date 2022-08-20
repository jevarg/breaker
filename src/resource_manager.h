#pragma once

#define TILE_WIDTH          16
#define TILE_HEIGHT         TILE_WIDTH

#define RES_TILESET_PATH    "../breaker.png"

#define TILESET_RECT(i) { .w = TILE_WIDTH, .h = TILE_HEIGHT, .x = TILE_WIDTH * i, .y = 0 }

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef enum resource_type_e
{
    RES_TEXTURE_TYPE = 0
} resource_type_t;

typedef enum resource_id_t
{
    TEX_BRICK = 0,
    TEX_CRACKS,
    TEX_BAR_LEFT,
    TEX_BAR_BODY,
    TEX_BAR_RIGHT,
    TEX_BALL,
} resource_id_t;

typedef struct texture_t
{
    int id;
    SDL_Texture *texture;
} texture_t;


typedef struct resource_manager_t
{
    SDL_Texture *tileset;
} resource_manager_t;


bool load_texture(resource_manager_t *mgr, SDL_Renderer *renderer, resource_id_t id, const char *path);
void unload_texture(resource_manager_t *mgr, resource_id_t id);
void load_tileset(resource_manager_t *mgr, SDL_Renderer *renderer);
