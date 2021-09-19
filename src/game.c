#include "game.h"
#include "window.h"
#include "utils.h"

void game_loop(t_ui *ui, t_game *game)
{
    while (SDL_HasEvent(SDL_QUIT) == SDL_FALSE)
    {
        SDL_PumpEvents();
        input_update(ui->input);
        bar_update(game->bar, ui->input);
        SDL_RenderClear(ui->renderer);

        bar_draw(game->bar, ui->renderer);

        SDL_RenderPresent(ui->renderer);
        SDL_Delay(1000 / 60); // TODO: delta time
    }
}

void game_start(t_ui *ui)
{
    t_game *game = game_init(ui);
    if (game == NULL)
    {
        print_error("Unable to init game");
        return;
    }

    game_loop(ui, game);
    game_destroy(game);
}

t_game *game_init(t_ui *ui)
{
    t_game *game = malloc(sizeof(t_game));
    if (game == NULL)
    {
        return NULL;
    }

    game->bar = NULL;
    game->ball = NULL;

    game->bar = bar_init(ui->renderer);
    if (game->bar == NULL)
    {
        print_error("Unable to init bar");
        game_destroy(game);

        return NULL;
    }

    // if (game->ball == NULL)
    // {
    //     print_error("Unable to init ball");
    //     game_destroy(game);

    //     return NULL;
    // }

    return game;
}

void game_destroy(t_game *game)
{
    if (game == NULL)
    {
        return;
    }

    if (game->ball != NULL)
    {
        free(game->ball);
    }

    if (game->bar != NULL)
    {
        free(game->bar);
    }

    free(game);
}