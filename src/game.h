#pragma once

#include "ball.h"
#include "bar.h"
#include "brick.h"
#include "ui.h"
#include "resource_manager.h"
#include "particle.h"
#include "particle_list.h"

#define TARGET_FPS 60
#define MAX_PARTICLES 100

typedef enum game_state_t
{
    GAME_STATE_RUNNING,
    GAME_STATE_WON,
    GAME_STATE_GAME_OVER
} game_state_t;
typedef struct game_t
{
    resource_manager_t *resource_mgr;
    bar_t *bar;
    ball_t *ball;
    brick_t **bricks;
    particle_t **particles;
    particle_list_node_t *particles_list;

    uint8_t particles_nb;
    uint32_t brick_nb;
    game_state_t state;
} game_t;

game_t *game_init();
void game_start(ui_t *ui);
void game_restart(game_t *game);
void game_destroy(game_t *game);
void game_draw(game_t *game, ui_t *ui);