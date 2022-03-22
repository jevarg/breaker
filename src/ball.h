#pragma once

#include <SDL2/SDL.h>

#include "input.h"
#include "vec2.h"
#include "resource_manager.h"

#define BALL_RADIUS 16.0f
#define BALL_DEFAULT_SPEED 300
#define BALL_MAX_SPEED 3000

typedef struct s_ball
{
    fvec2 pos;
    vec2 dir;
    fvec2 velocity;

    SDL_FRect bounding_box;
    SDL_Texture *texture;
} t_ball;

t_ball *ball_init(SDL_Renderer *renderer);
void ball_destroy(t_ball *ball);
void ball_update(t_ball *ball, t_input *input, float delta);
void ball_draw(t_ball *ball, t_resource_manager *mgr, SDL_Renderer *renderer);