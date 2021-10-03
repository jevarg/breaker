#include <stdlib.h>
#include "brick.h"
#include "utils.h"

t_brick *brick_init(SDL_Renderer *renderer)
{
    t_brick *brick = malloc(sizeof(t_brick));
    if (brick == NULL)
    {
        print_error("Unable to initialize brick");
        return NULL;
    }

    brick->texture = NULL;
    brick->pos = (vec2){0};
    brick->state = NORMAL;
    brick->bounding_box = (SDL_Rect){
        .x = 0,
        .y = 0,
        .w = BRICK_WIDTH,
        .h = BRICK_HEIGHT};

    SDL_Surface *s = SDL_CreateRGBSurface(0, BRICK_WIDTH, BRICK_HEIGHT, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    if (s == NULL)
    {
        print_error("Unable to create brick surface!");
        brick_destroy(brick);

        return NULL;
    }

    SDL_FillRect(s, NULL, 0xffffffff);

    // DEBUG !
    {
        SDL_Rect top = {.w = BRICK_WIDTH, .h = 1, .x = 0, .y = 0};
        SDL_Rect bottom = {.w = BRICK_WIDTH, .h = 1, .x = 0, .y = BRICK_HEIGHT - 1};
        SDL_Rect left = {.w = 1, .h = BRICK_HEIGHT, .x = 0, .y = 0};
        SDL_Rect right = {.w = 1, .h = BRICK_HEIGHT, .x = BRICK_WIDTH - 1, .y = 0};

        SDL_FillRect(s, &top, 0xff0000ff);
        SDL_FillRect(s, &bottom, 0xff0000ff);
        SDL_FillRect(s, &left, 0xff0000ff);
        SDL_FillRect(s, &right, 0xff0000ff);
    }

    brick->texture = SDL_CreateTextureFromSurface(renderer, s);
    if (brick->texture == NULL)
    {
        print_error("Unable to create brick texture");
        brick_destroy(brick);

        return NULL;
    }

    return brick;
}

void brick_destroy(t_brick *brick)
{
    if (brick == NULL)
    {
        return;
    }

    if (brick->texture != NULL)
    {
        SDL_DestroyTexture(brick->texture);
    }

    free(brick);
}

void brick_update(t_brick *brick, t_input *input)
{
    brick->bounding_box.x = brick->pos.x;
    brick->bounding_box.y = brick->pos.y;
}

void brick_draw(t_brick *brick, SDL_Renderer *renderer)
{
    if (brick->state != NORMAL)
    {
        return;
    }

    SDL_Rect rect = {
        .w = BRICK_WIDTH,
        .h = BRICK_HEIGHT,
        .x = brick->pos.x,
        .y = brick->pos.y};

    SDL_RenderCopy(renderer, brick->texture, NULL, &rect);
}

void brick_break(t_brick *brick)
{
    brick->bounding_box.w = 0;
    brick->bounding_box.h = 0;
    brick->state = BROKEN;
}