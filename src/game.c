#include "game.h"
#include "window.h"
#include "utils.h"
#include "map.h"
#include "collisions.h"
#include "brick.h"

void game_update(t_game *game, t_ui *ui, float delta)
{
    input_update(ui->input);
    bar_update(game->bar, ui->input);
    ball_update(game->ball, ui->input, delta);

    for (u_int i = 0; i < game->brick_nb; ++i)
    {
        brick_update(game->bricks[i], ui->input);
    }
}

Uint32 fps_counter(Uint32 interval, void *param)
{
    int *fps = param;

    printf("FPS %d\n", *fps);
    *fps = 0;

    return interval; // We want a steady interval
}

void game_loop(t_game *game, t_ui *ui)
{
    float delta = 0;
    int fps = 0;
    Uint64 frame_start_time = 0;
    Uint64 frame_end_time = 0;

    SDL_AddTimer(1000, fps_counter, &fps);

    while (ui->input->needs_exit == SDL_FALSE &&
           ui->input->kbd_state[SDL_SCANCODE_ESCAPE] == SDL_FALSE)
    {
        frame_start_time = SDL_GetTicks64();
        delta = (frame_start_time - frame_end_time) / 1000.0f;

        SDL_RenderClear(ui->renderer);
        SDL_PumpEvents();

        game_update(game, ui, delta);
        handle_collisions(game, ui, delta);

        bar_draw(game->bar, &game->resource_mgr, ui->renderer);
        ball_draw(game->ball, &game->resource_mgr, ui->renderer);

        for (u_int i = 0; i < game->brick_nb; ++i)
        {
            brick_draw(game->bricks[i], &game->resource_mgr, ui->renderer);
        }

        SDL_RenderPresent(ui->renderer);

        frame_end_time = SDL_GetTicks64();
        int elapsed_time = (frame_end_time - frame_start_time);
        int target_delay = (1000 / TARGET_FPS);
        int delay = target_delay - elapsed_time;

        if (delay > 0)
        {
            SDL_Delay(delay);
        }

        ++fps;
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

    // for (size_t i = 0; i < MAX_RESOURCES; ++i)
    // {
    //     game->resource_mgr.resources[i] = NULL;
    // }

    // load_texture(&game->resource_mgr, ui->renderer, TEX_CORPO, "../test.jpg");
    load_tileset(&game->resource_mgr, ui->renderer);

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