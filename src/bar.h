#pragma once

#include <SDL2/SDL.h>

#include "resource_manager.h"
#include "input.h"
#include "vec2.h"

#define BAR_WIDTH 128
#define BAR_HEIGHT 16

typedef struct s_bar
{
    vec2 pos;
    int force;

    SDL_Rect bounding_box;
    SDL_Texture *texture;
} t_bar;

t_bar *bar_init(SDL_Renderer *renderer);
void bar_destroy(t_bar *bar);
void bar_update(t_bar *bar, t_input *input);
void bar_draw(t_bar *bar, t_resource_manager *mgr, SDL_Renderer *renderer);