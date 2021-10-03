#pragma once

#include <SDL2/SDL.h>
#include "vec2.h"
#include "input.h"

#define BRICK_WIDTH 100
#define BRICK_HEIGHT 30

typedef enum e_brick_state
{
    DEFAULT,
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
void brick_draw(t_brick *brick, SDL_Renderer *renderer);
void brick_break(t_brick *brick);