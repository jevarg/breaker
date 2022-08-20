#include <stdlib.h>
#include "ball.h"
#include "utils.h"

ball_t *ball_init(SDL_Renderer *renderer)
{
    ball_t *ball = malloc(sizeof(ball_t));
    if (ball == NULL)
    {
        print_error("Unable to initialize ball");
        return NULL;
    }

    ball->texture = NULL;
    ball->velocity = (fvec2) {0};
    ball->pos = (fvec2) {0};
    ball->bounding_box = (SDL_FRect) {
        .x = 0.0f,
        .y = 0.0f,
        .w = BALL_RADIUS,
        .h = BALL_RADIUS
    };

    return ball;
}

void ball_destroy(ball_t *ball)
{
    if (ball == NULL)
    {
        return;
    }

    if (ball->texture != NULL)
    {
        SDL_DestroyTexture(ball->texture);
    }

    free(ball);
}

void ball_update_bounding_box(ball_t *ball)
{
    ball->bounding_box.x = ball->pos.x;
    ball->bounding_box.y = ball->pos.y;
}

void ball_update(ball_t *ball, input_t *input, float delta)
{
    if (ball->velocity.x == 0 && ball->velocity.y == 0)
    {
        if (input->kbd_state[SDL_SCANCODE_SPACE])
        {
            ball->velocity.y = -BALL_DEFAULT_SPEED;
        }
        else
        {
            ball->pos.x = (input->mouse_pos.x - BALL_RADIUS / 2);
            ball_update_bounding_box(ball);
        }

        return;
    }

    ball->pos.x += ball->velocity.x * delta;
    ball->pos.y += ball->velocity.y * delta;

    ball_update_bounding_box(ball);
}

void ball_draw(ball_t *ball, resource_manager_t *mgr, SDL_Renderer *renderer)
{
    SDL_FRect dstrect = {
        .h = BALL_RADIUS,
        .w = BALL_RADIUS,
        .x = ball->pos.x,
        .y = ball->pos.y
    };

    SDL_Rect srcrect = TILESET_RECT(TEX_BALL);

    SDL_RenderCopyF(renderer, mgr->tileset, &srcrect, &dstrect);
}
