#pragma once

#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

#include "input.h"

typedef struct s_ui
{
    SDL_Window *win;
    SDL_Renderer *renderer;
    input_t *input;
    TTF_Font *font;
} ui_t;

ui_t *ui_init();
void ui_destroy(ui_t *ui);