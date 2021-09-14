#pragma once

#include <SDL2/SDL.h>

typedef struct s_input
{
    SDL_Point mouse_pos;
} t_input;

void input_update(t_input *input);