#include "collisions.h"
#include "window.h"

void ball_world_collisions(t_game *game, t_ui *ui)
{
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
}

void ball_bar_collisions(t_game *game, t_ui *ui)
{
    SDL_Rect A = {
        .x = (int) game->ball->bounding_box.x,
        .y = (int) game->ball->bounding_box.y,
        .w = (int) game->ball->bounding_box.w,
        .h = (int) game->ball->bounding_box.h
    };

    if (SDL_HasIntersection(&A, &game->bar->bounding_box) == SDL_TRUE) {
        game->ball->dir.y = -game->ball->dir.y;
        game->ball->dir.x = ui->input->mouse_dir.x;

        game->ball->velocity.x = (SDL_min(SDL_max(game->bar->force * 50, BALL_DEFAULT_SPEED), BALL_MAX_SPEED));
        game->ball->velocity.y = (SDL_min(SDL_max(game->bar->force * 50, BALL_DEFAULT_SPEED), BALL_MAX_SPEED * 2));
    }
}

void ball_bricks_collisions(t_game *game, t_ui *ui)
{
    SDL_Rect A = {
        .x = (int) game->ball->bounding_box.x,
        .y = (int) game->ball->bounding_box.y,
        .w = (int) game->ball->bounding_box.w,
        .h = (int) game->ball->bounding_box.h
    };

    for (u_int i = 0; i < game->brick_nb; ++i)
    {
        if (SDL_HasIntersection(&A, &game->bricks[i]->bounding_box) == SDL_TRUE) {
            game->ball->dir.y = -game->ball->dir.y;
            game->ball->dir.x = ui->input->mouse_dir.x;

            brick_take_damage(game->bricks[i]);

            return;
        }
    }
}

void handle_collisions(t_game *game, t_ui *ui, float delta)
{
    ball_world_collisions(game, ui);
    ball_bar_collisions(game, ui);
    ball_bricks_collisions(game, ui);
}