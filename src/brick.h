#pragma once

#include <SDL2/SDL.h>

#include "vec2.h"
#include "input.h"
#include "resource_manager.h"

#define BRICK_WIDTH (16 * 3)
#define BRICK_HEIGHT (16 * 3)

typedef enum e_brick_state
{
    BRICK_STATE_DEFAULT,
    BRICK_STATE_DAMAGED,
    BRICK_STATE_BROKEN
} t_brick_state;

typedef struct s_brick
{
    vec2 pos;
    SDL_FRect bounding_box;
    SDL_Texture *texture;
    t_brick_state state;
    texture_id_t res;
} brick_t;

brick_t *brick_init(SDL_Renderer *renderer);
void brick_destroy(brick_t *brick);
void brick_update(brick_t *brick, input_t *input);
void brick_draw(brick_t *brick, resource_manager_t *mgr, SDL_Renderer *renderer);
void brick_take_damage(brick_t *brick, resource_manager_t *mgr);