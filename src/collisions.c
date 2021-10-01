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
    SDL_Rect inter;
    if (SDL_IntersectRect(&game->ball->bounding_box, &game->bar->bounding_box, &inter) == SDL_TRUE) {
        game->ball->dir.y = -game->ball->dir.y;
        game->ball->dir.x = ui->input->mouse_dir.x;

        game->ball->velocity.x = (SDL_min(SDL_max(game->bar->force, 5), 10));
        game->ball->velocity.y = (SDL_min(SDL_max(game->bar->force, 5), 20));
    }
}

void handle_collisions(t_game *game, t_ui *ui)
{
    ball_world_collisions(game, ui);
    ball_bar_collisions(game, ui);
}