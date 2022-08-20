#pragma once

#include <SDL2/SDL.h>

typedef enum e_dir {
    NONE,
    LEFT,
    RIGHT
} t_dir;

typedef struct s_input
{
    const Uint8 *kbd_state;
    
    SDL_bool needs_exit;
    SDL_Point mouse_pos;
    SDL_Point mouse_delta;
    SDL_Point mouse_dir;
} input_t;

void input_update(input_t *input);