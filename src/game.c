#include "game.h"
#include "window.h"
#include "utils.h"
#include "map.h"

void game_update(t_game *game, t_ui *ui)
{
    input_update(ui->input);
    bar_update(game->bar, ui->input);
    ball_update(game->ball, ui->input);

    if (game->ball->pos.x > WIN_WIDTH ||
        game->ball->pos.x < 0)
    {
        game->ball->dir.x = -game->ball->dir.x;
    }

    if (game->ball->pos.y > WIN_HEIGHT ||
        game->ball->pos.y < 0)
    {
        game->ball->dir.y = -game->ball->dir.y;
    }

    SDL_Rect inter;
    if (SDL_IntersectRect(&game->ball->bounding_box, &game->bar->bounding_box, &inter) == SDL_TRUE) {
        game->ball->dir.y = -game->ball->dir.y;
        game->ball->dir.x = ui->input->mouse_dir.x;

        game->ball->velocity.x = (SDL_min(SDL_max(game->bar->force, 5), 10));
        game->ball->velocity.y = (SDL_min(SDL_max(game->bar->force, 5), 20));
    }
}

void game_loop(t_game *game, t_ui *ui)
{
    while (ui->input->needs_exit == SDL_FALSE &&
           ui->input->kbd_state[SDL_SCANCODE_ESCAPE] == SDL_FALSE)
    {
        SDL_RenderClear(ui->renderer);
        SDL_PumpEvents();

        game_update(game, ui);

        bar_draw(game->bar, ui->renderer);
        ball_draw(game->ball, ui->renderer);

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

    game_loop(game, ui);
    game_destroy(game);
}

t_game *game_init(t_ui *ui)
{
    t_game *game = malloc(sizeof(t_game));
    if (game == NULL)
    {
        return NULL;
    }

    game->bar = bar_init(ui->renderer);
    if (game->bar == NULL)
    {
        print_error("Unable to init bar");
        game_destroy(game);

        return NULL;
    }

    game->ball = ball_init(ui->renderer);
    if (game->ball == NULL)
    {
        print_error("Unable to init ball");
        game_destroy(game);

        return NULL;
    }

    game->bar->pos.y = WIN_HEIGHT - 100;
    game->ball->pos.y = WIN_HEIGHT - 100 - BALL_RADIUS;

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