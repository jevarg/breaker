#pragma once

#include <SDL2/SDL.h>

#include "vec2.h"
#include "input.h"
#include "resource_manager.h"

#define BRICK_WIDTH 96
#define BRICK_HEIGHT 16

typedef enum e_brick_state
{
    DEFAULT,
    DAMAGED,
    BROKEN
} t_brick_state;

typedef struct s_brick
{
    vec2 pos;
    SDL_Rect bounding_box;
    SDL_Texture *texture;
    t_brick_state state;
} t_brick;

t_brick *brick_init(SDL_Renderer *renderer);
void brick_destroy(t_brick *brick);
void brick_update(t_brick *brick, t_input *input);
void brick_draw(t_brick *brick, t_resource_manager *mgr, SDL_Renderer *renderer);
void brick_take_damage(t_brick *brick);