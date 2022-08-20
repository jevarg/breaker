#pragma once

#include <SDL2/SDL.h>

#include "input.h"
#include "vec2.h"
#include "resource_manager.h"

#define BALL_RADIUS 16.0f
#define BALL_DEFAULT_SPEED 10
#define BALL_MAX_SPEED 10

typedef struct ball_t
{
    fvec2 pos;
    fvec2 velocity;

    SDL_FRect bounding_box;
    SDL_Texture *texture;
} ball_t;

ball_t *ball_init(SDL_Renderer *renderer);
void ball_destroy(ball_t *ball);
void ball_update(ball_t *ball, input_t *input, float delta);
void ball_draw(ball_t *ball, resource_manager_t *mgr, SDL_Renderer *renderer);