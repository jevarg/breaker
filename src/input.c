#include "input.h"

void input_update(input_t *input)
{
    int prev_x = input->mouse_pos.x;
    int prev_y = input->mouse_pos.y;

    // SDL_PumpEvents();
    SDL_GetMouseState(&input->mouse_pos.x, &input->mouse_pos.y);

    input->mouse_delta.x = prev_x - input->mouse_pos.x;
    input->mouse_delta.y = prev_y - input->mouse_pos.y;

    if (prev_x < input->mouse_pos.x)
    {
        input->mouse_dir.x = 1;
    }
    else if (prev_x > input->mouse_pos.x)
    {
        input->mouse_dir.x = -1;
    }
    else
    {
        input->mouse_dir.x = 0;
    }

    if (prev_y < input->mouse_pos.y)
    {
        input->mouse_dir.y = 1;
    }
    else if (prev_y > input->mouse_pos.y)
    {
        input->mouse_dir.y = -1;
    }
    else
    {
        input->mouse_dir.y = 0;
    }

    if (SDL_HasEvent(SDL_QUIT) == SDL_TRUE)
    {
        input->needs_exit = SDL_TRUE;
    }
}