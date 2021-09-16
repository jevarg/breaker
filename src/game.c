#include "game.h"
#include "window.h"

void start_game(t_ui *ui)
{
    t_game game;

    game.bar.y = WIN_HEIGHT - 50;

    while (SDL_HasEvent(SDL_QUIT) == SDL_FALSE)
    {
        SDL_SetRenderDrawColor(ui->renderer, 0, 0, 0, 255);
        SDL_RenderClear(ui->renderer);
        SDL_PumpEvents();
        input_update(ui->input);

        game.bar.x = ui->input->mouse_pos.x - (BAR_WIDTH / 2);

        SDL_Rect bar = {
            .h = BAR_HEIGHT,
            .w = BAR_WIDTH,
            .x = game.bar.x,
            .y = game.bar.y
        };

        SDL_SetRenderDrawColor(ui->renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(ui->renderer, &bar);
        SDL_RenderPresent(ui->renderer);
        SDL_Delay(1000 / 60); // TODO: delta time
    }
}