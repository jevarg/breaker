#include <stdint.h>

#include "game.h"
#include "window.h"
#include "utils.h"
#include "map.h"
#include "collisions.h"
#include "brick.h"
#include "text.h"

void game_update(game_t *game, ui_t *ui, float delta)
{
    input_update(ui->input);

    switch (game->state)
    {
    case GAME_STATE_RUNNING:
        bar_update(game->bar, ui->input);
        ball_update(game->ball, ui->input, delta);

        for (size_t i = 0; i < game->brick_nb; ++i)
        {
            brick_update(game->bricks[i], ui->input);
        }
        break;

    case GAME_STATE_GAME_OVER:
        if (ui->input->kbd_state[SDL_SCANCODE_RETURN] == SDL_TRUE)
        {
            game_restart(game);
        }
        break;

    default:
        break;
    }
}

void game_draw(game_t *game, ui_t *ui)
{
    switch (game->state)
    {
    case GAME_STATE_GAME_OVER:
        draw_text("GAME OVER", ui, 0, 0, CENTERED_X | CENTERED_Y);
        draw_text("press enter to try again", ui, 0, WIN_HEIGHT - 50, CENTERED_X);
        break;
    
    default:
        break;
    }
}

void game_restart(game_t *game)
{
    game->ball->velocity.x = 0;
    game->ball->velocity.y = 0;
    game->bar->pos.y = WIN_HEIGHT - 100;
    game->ball->pos.y = WIN_HEIGHT - 100 - BALL_RADIUS;

    for (size_t i = 0; i < game->brick_nb; ++i)
    {
        game->bricks[i]->state = BRICK_STATE_DEFAULT;
    }
    
    game->state = GAME_STATE_RUNNING;
}

Uint32 fps_counter(Uint32 interval, void *param)
{
    int *fps = param;

    printf("FPS %d\n", *fps);
    *fps = 0;

    return interval; // We want a steady interval
}

void game_loop(game_t *game, ui_t *ui)
{
    // float delta = 0;
    // int fps = 0;
    // Uint64 frame_start_time = 0;
    // Uint64 frame_end_time = 0;

    // SDL_AddTimer(1000, fps_counter, &fps);

    while (ui->input->needs_exit == SDL_FALSE &&
           ui->input->kbd_state[SDL_SCANCODE_ESCAPE] == SDL_FALSE)
    {
        int target_delay = (1000 / TARGET_FPS);
        // frame_start_time = SDL_GetTicks64();
        // delta = (frame_start_time - frame_end_time);

        SDL_RenderClear(ui->renderer);
        SDL_PumpEvents();

        game_update(game, ui, 1.0f);
        handle_collisions(game, ui, 1.0f);

        bar_draw(game->bar, &game->resource_mgr, ui->renderer);
        ball_draw(game->ball, &game->resource_mgr, ui->renderer);

        for (size_t i = 0; i < game->brick_nb; ++i)
        {
            brick_draw(game->bricks[i], &game->resource_mgr, ui->renderer);
        }

        game_draw(game, ui);

        SDL_RenderPresent(ui->renderer);
        SDL_Delay(target_delay);

        // frame_end_time = SDL_GetTicks64();
        // int elapsed_time = (frame_end_time - frame_start_time);
        // int target_delay = (1000 / TARGET_FPS);
        // int delay = target_delay - elapsed_time;

        // if (delay > 0)
        // {
            // SDL_Delay(delay);
        // }

        // ++fps;
    }
}

bool game_init_bricks(game_t *game, ui_t *ui)
{
    uint32_t bricks_per_row = (WIN_WIDTH / BRICK_WIDTH);
    uint32_t rows_nb = 3;
    game->brick_nb = bricks_per_row * rows_nb;

    game->bricks = malloc(sizeof(brick_t *) * game->brick_nb);
    if (game->bricks == NULL)
    {
        return false;
    }

    for (size_t i = 0; i < game->brick_nb; ++i)
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

void game_start(ui_t *ui)
{
    game_t *game = game_init(ui);
    if (game == NULL)
    {
        print_error("Unable to init game");
        return;
    }

    game_init_bricks(game, ui);

    game_loop(game, ui);
    game_destroy(game);
}

game_t *game_init(ui_t *ui)
{
    game_t *game = malloc(sizeof(game_t));
    if (game == NULL)
    {
        return NULL;
    }

    game->state = GAME_STATE_RUNNING;
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

    game_restart(game);

    return game;
}

void game_destroy(game_t *game)
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
        for (size_t i = 0; i < game->brick_nb; ++i)
        {
            brick_destroy(game->bricks[i]);
        }

        free(game->bricks);
    }

    free(game);
}