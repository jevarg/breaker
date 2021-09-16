#pragma once

#include "ui.h"

#define BAR_WIDTH 100
#define BAR_HEIGHT 10

typedef struct s_bar
{
    int x;
    int y;
} t_bar;

typedef struct s_brick
{
    int x;
    int y;
} t_brick;

typedef struct s_ball
{
    int x;
    int y;
} t_ball;

typedef struct s_game
{
    t_bar bar;
    t_ball ball;
    // t_brick bricks[];
} t_game;

void start_game(t_ui *ui);