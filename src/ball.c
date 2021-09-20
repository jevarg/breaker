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
    ball->dir.x = 0;
    ball->dir.y = 0;
    ball->pos.x = 0;
    ball->pos.y = 0;

    SDL_Surface *s = SDL_CreateRGBSurface(0, BALL_RADIUS, BALL_RADIUS, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    if (s == NULL)
    {
        print_error("Unable to create ball surface!");
        ball_destroy(ball);

        return NULL;
    }
    
    SDL_FillRect(s, NULL, 0x0000ffff);
    ball->texture = SDL_CreateTextureFromSurface(renderer, s);
    if (ball->texture == NULL)
    {
        print_error("Unable to create ball texture");
        ball_destroy(ball);

        return NULL;
    }

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

void ball_update(t_ball *ball, t_input *input)
{
    if (ball->dir.x == 0 && ball->dir.y == 0)
    {
        if (input->mouse_pos.x >= 700)
        {
            ball->dir.y = -1;
        }

        ball->pos.x = (input->mouse_pos.x - BALL_RADIUS / 2);
        return;
    }

    if (ball->dir.x >= 1)
    {
        ball->pos.x += 1;
    }
    else if (ball->dir.x <= -1)
    {
        ball->pos.x -= 1;
    }

    if (ball->dir.y >= 1)
    {
        ball->pos.y += 1;
    }
    else if (ball->dir.y <= -1)
    {
        ball->pos.y -= 1;
    }
}

void ball_draw(t_ball *ball, SDL_Renderer *renderer)
{
    SDL_Rect rect = {
        .h = BALL_RADIUS,
        .w = BALL_RADIUS,
        .x = ball->pos.x,
        .y = ball->pos.y
    };

    SDL_RenderCopy(renderer, ball->texture, NULL, &rect);
}
