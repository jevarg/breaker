#include "input.h"

void input_update(t_input *input)
{
    SDL_GetMouseState(&(input->mouse_pos.x), &(input->mouse_pos.y));
}