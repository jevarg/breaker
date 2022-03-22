#pragma once

#include "ball.h"
#include "bar.h"
#include "brick.h"
#include "ui.h"
#include "resource_manager.h"

#define TARGET_FPS 60

typedef struct s_game
{
    t_resource_manager resource_mgr;
    t_bar *bar;
    t_ball *ball;
    t_brick **bricks;

    u_int brick_nb;
} t_game;

void game_start(t_ui *ui);
t_game *game_init();
void game_destroy(t_game *game);