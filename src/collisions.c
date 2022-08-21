#include "collisions.h"
#include "window.h"
#include "particle.h"

void ball_world_collisions(game_t *game, ui_t *ui)
{
    if (game->ball->pos.x > WIN_WIDTH ||
        game->ball->pos.x < 0)
    {
        game->ball->velocity.x = -game->ball->velocity.x;
    }

    if (game->ball->pos.y > WIN_HEIGHT ||
        game->ball->pos.y < 0)
    {
        game->ball->velocity.y = 0;
        game->state = GAME_STATE_GAME_OVER;
    }
}

void ball_bar_collisions(game_t *game, ui_t *ui)
{
    if (SDL_HasIntersectionF(&game->ball->bounding_box, &game->bar->bounding_box) == SDL_TRUE) {
        game->ball->velocity.y = -game->ball->velocity.y;

        if (ui->input->mouse_dir.x) {
            game->ball->velocity.x = SDL_min(ui->input->mouse_dir.x * game->bar->force, BALL_MAX_SPEED);
        }
    }
}

void ball_bricks_collisions(game_t *game, ui_t *ui)
{
    for (size_t i = 0; i < game->brick_nb; ++i)
    {
        brick_t *brick = game->bricks[i];

        if (SDL_HasIntersectionF(&game->ball->bounding_box, &brick->bounding_box) == SDL_TRUE) {
            game->ball->velocity.y = -game->ball->velocity.y;

            brick_take_damage(brick);
            
            uint8_t particles_nb = (rand() + 1) % 5;
            for (size_t i = 0; i < particles_nb; ++i)
            {
                particle_t *particle = particle_create(
                    (fvec2) { .x = brick->pos.x + rand() % 16 * 3, .y = brick->pos.y + BRICK_HEIGHT },
                    (vec2) { .x = rand() % 1, .y = 1 },
                    brick->res
                );

                game->particles[game->particles_nb + i] = particle;
            }

            game->particles_nb += particles_nb;
            printf("Number of particles: %d\n", game->particles_nb);
            return;
        }
    }
}

void handle_collisions(game_t *game, ui_t *ui, float delta)
{
    ball_world_collisions(game, ui);
    ball_bar_collisions(game, ui);
    ball_bricks_collisions(game, ui);
}