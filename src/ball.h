#pragma once

#include <SDL2/SDL.h>
#include "input.h"
#include "vec2.h"

#define BALL_RADIUS 10

typedef struct s_ball
{
    vec2 pos;
    vec2 dir;
    SDL_Texture *texture;
} t_ball;

t_ball *ball_init(SDL_Renderer *renderer);
void ball_destroy(t_ball *ball);
void ball_update(t_ball *ball, t_input *input);
void ball_draw(t_ball *ball, SDL_Renderer *renderer);