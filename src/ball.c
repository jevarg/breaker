#include <stdlib.h>
#include "ball.h"
#include "utils.h"

t_ball *ball_init(SDL_Renderer *renderer)
{
    t_ball *ball = malloc(sizeof(t_ball));
    if (ball == NULL)
    {
        print_error("Unable to initialize ball");
        return NULL;
    }

    ball->texture = NULL;
    ball->velocity = (fvec2) {.x = 1.0f, .y = BALL_DEFAULT_SPEED};
    ball->dir = (vec2) {0};
    ball->pos = (fvec2) {0};
    ball->bounding_box = (SDL_FRect) {
        .x = 0.0f,
        .y = 0.0f,
        .w = BALL_RADIUS,
        .h = BALL_RADIUS
    };

    return ball;
}

void ball_destroy(t_ball *ball)
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

void ball_update_bounding_box(t_ball *ball)
{
    ball->bounding_box.x = ball->pos.x;
    ball->bounding_box.y = ball->pos.y;
}

void ball_update(t_ball *ball, t_input *input, float delta)
{
    if (ball->dir.x == 0 && ball->dir.y == 0)
    {
        if (input->kbd_state[SDL_SCANCODE_SPACE])
        {
            ball->dir.y = -1;
        }
        else
        {
            ball->pos.x = (input->mouse_pos.x - BALL_RADIUS / 2);
            ball_update_bounding_box(ball);
        }

        return;
    }

    if (ball->dir.x >= 1)
    {
        ball->pos.x += (ball->velocity.x * delta);
    }
    else if (ball->dir.x <= -1)
    {
        ball->pos.x -= (ball->velocity.x * delta);
    }

    if (ball->dir.y >= 1)
    {
        ball->pos.y += (ball->velocity.y * delta);
    }
    else if (ball->dir.y <= -1)
    {
        ball->pos.y -= (ball->velocity.y * delta);
    }

    ball_update_bounding_box(ball);
}

void ball_draw(t_ball *ball, t_resource_manager *mgr, SDL_Renderer *renderer)
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
