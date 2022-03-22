#pragma once

#define TILE_WIDTH          16
#define TILE_HEIGHT         TILE_WIDTH

#define RES_TILESET_PATH    "../breaker.png"

#define TILESET_RECT(i) { .w = TILE_WIDTH, .h = TILE_HEIGHT, .x = TILE_WIDTH * i, .y = 0 }

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef enum e_resource_type
{
    RES_TEXTURE_TYPE = 0
} t_resource_type;

typedef enum e_resource_id
{
    TEX_BRICK = 0,
    TEX_CRACKS,
    TEX_BAR_LEFT,
    TEX_BAR_BODY,
    TEX_BAR_RIGHT,
    TEX_BALL,
} t_resource_id;

typedef struct s_texture
{
    int id;
    SDL_Texture *texture;
} t_texture;


typedef struct s_resource_manager
{
    SDL_Texture *tileset;
} t_resource_manager;


bool load_texture(t_resource_manager *mgr, SDL_Renderer *renderer, t_resource_id id, const char *path);
void unload_texture(t_resource_manager *mgr, t_resource_id id);
void load_tileset(t_resource_manager *mgr, SDL_Renderer *renderer);
