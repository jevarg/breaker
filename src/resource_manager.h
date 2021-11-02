#pragma once

#define MAX_RESOURCES 64

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef enum e_resource_type
{
    RES_TEXTURE_TYPE = 0
} t_resource_type;

typedef struct s_texture
{
    int id;
    SDL_Texture *texture;
} t_texture;


typedef struct s_resource_manager
{
    int last_id;
    t_texture *textures[MAX_RESOURCES];
} t_resource_manager;


bool load_texture(t_resource_manager *mgr, const char *path);