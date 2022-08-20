#include <SDL2/SDL_image.h>

#include "resource_manager.h"
#include "utils.h"

void load_tileset(resource_manager_t *mgr, SDL_Renderer *renderer)
{
    SDL_Surface *loaded_surface = IMG_Load(RES_TILESET_PATH);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, loaded_surface);

    mgr->tileset = tex;
}