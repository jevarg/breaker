#include "game.h"
#include "window.h"
#include "utils.h"
#include "map.h"
#include "collisions.h"
#include "brick.h"

void game_update(t_game *game, t_ui *ui)
{
    input_update(ui->input);
    bar_update(game->bar, ui->input);
    ball_update(game->ball, ui->input);

    for (u_int i = 0; i < game->brick_nb; ++i)
    {
        brick_update(game->bricks[i], ui->input);
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
        handle_collisions(game, ui);

        bar_draw(game->bar, ui->renderer);
        ball_draw(game->ball, ui->renderer);

        for (u_int i = 0; i < game->brick_nb; ++i)
        {
            brick_draw(game->bricks[i], ui->renderer);
        }

        SDL_RenderPresent(ui->renderer);
        SDL_Delay(1000 / 60); // TODO: delta time
    }
}

bool game_init_bricks(t_game *game, t_ui *ui)
{
    u_int bricks_per_row = (WIN_WIDTH / BRICK_WIDTH);
    u_int rows_nb = 3;
    game->brick_nb = bricks_per_row * rows_nb;

    game->bricks = malloc(sizeof(t_brick *) * game->brick_nb);
    if (game->bricks == NULL)
    {
        return false;
    }

    for (u_int i = 0; i < game->brick_nb; ++i)
    {
        game->bricks[i] = brick_init(ui->renderer);
        if (game->bricks[i] == NULL)
        {
            return false;
        }

        game->bricks[i]->pos.x = (BRICK_WIDTH * i) % WIN_WIDTH;
        game->bricks[i]->pos.y = BRICK_HEIGHT * (i / bricks_per_row);
    }

    return true;
}

void game_start(t_ui *ui)
{
    t_game *game = game_init(ui);
    if (game == NULL)
    {
        print_error("Unable to init game");
        return;
    }

    game_init_bricks(game, ui);

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

    game->resource_mgr.last_id = -1;
    for (size_t i = 0; i < MAX_RESOURCES; ++i)
    {
        game->resource_mgr.textures[i] = NULL;
    }

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

    if (game->bricks != NULL)
    {
        for (u_int i = 0; i < game->brick_nb; ++i)
        {
            brick_destroy(game->bricks[i]);
        }

        free(game->bricks);
    }

    free(game);
}