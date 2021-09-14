#pragma once

#include <SDL2/SDL.h>
#include "input.h"

typedef struct s_ui
{
    SDL_Window *win;
    SDL_Renderer *renderer;
    t_input *input;
} t_ui;

t_ui *ui_init();
void ui_destroy(t_ui *ui);