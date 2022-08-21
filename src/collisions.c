#ifdef __APPLE__
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL2/SDL_mixer.h>
#endif

#include "collisions.h"
#include "window.h"
#include "particle.h"

void ball_world_collisions(game_t *game, ui_t *ui)
{
    if (game->ball->pos.x > WIN_WIDTH ||
        game->ball->pos.x < 0)
    {
        game->ball->velocity.x = -game->ball->velocity.x;
        Mix_PlayChannel(-1, game->resource_mgr->sounds[SFX_BALL_BOUNCE], 0);
    }

    if (game->ball->pos.y < 0)
    {
        game->ball->velocity.y = 0;
        Mix_PlayChannel(-1, game->resource_mgr->sounds[SFX_BALL_BOUNCE], 0);
    }

    if (game->ball->pos.y > WIN_HEIGHT)
    {
        game->state = GAME_STATE_GAME_OVER;
    }
}

void ball_bar_collisions(game_t *game, ui_t *ui)
{
    if (game->ball->velocity.x == 0 &&
        game->ball->velocity.y == 0)
    {
        // Ball is not moving
        return;
    }

    if (SDL_HasIntersectionF(&game->ball->bounding_box, &game->bar->bounding_box) == SDL_TRUE) {
        game->ball->velocity.y = -game->ball->velocity.y;

        if (ui->input->mouse_dir.x) {
            game->ball->velocity.x = SDL_min(ui->input->mouse_dir.x * game->bar->force, BALL_MAX_SPEED);
        }

        Mix_PlayChannel(-1, game->resource_mgr->sounds[SFX_BALL_BOUNCE], 0);
    }
}

void ball_bricks_collisions(game_t *game, ui_t *ui)
{
    for (size_t i = 0; i < game->brick_nb; ++i)
    {
        brick_t *brick = game->bricks[i];

        if (SDL_HasIntersectionF(&game->ball->bounding_box, &brick->bounding_box) == SDL_TRUE) {
            game->ball->velocity.y = -game->ball->velocity.y;

            brick_take_damage(brick, game->resource_mgr);
            
            uint8_t particles_nb = (rand() % 5) + 1;
            printf("particles_nb: %d\n", particles_nb);

            for (size_t i = 0; i < particles_nb; ++i)
            {
                int x_offset = rand() % BRICK_WIDTH;
                int y_offset = rand() % BRICK_HEIGHT;

                particle_t *particle = particle_create(
                    (fvec2) {
                        .x = brick->pos.x + x_offset,
                        .y = brick->pos.y + y_offset
                    },
                    (vec2) {
                        .x = (rand() % 1) ? 1 : -1,
                        .y = 1
                    },
                    TEX_BRICK_PARTICLES
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