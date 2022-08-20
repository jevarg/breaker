#pragma once

#include <SDL2/SDL.h>

#include "resource_manager.h"
#include "input.h"
#include "vec2.h"

#define BAR_WIDTH 128
#define BAR_HEIGHT 16

typedef struct bar_t
{
    vec2 pos;
    int force;

    SDL_FRect bounding_box;
    SDL_Texture *texture;
} bar_t;

bar_t *bar_init(SDL_Renderer *renderer);
void bar_destroy(bar_t *bar);
void bar_update(bar_t *bar, input_t *input);
void bar_draw(bar_t *bar, resource_manager_t *mgr, SDL_Renderer *renderer);