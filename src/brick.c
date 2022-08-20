#include <stdlib.h>
#include "brick.h"
#include "utils.h"

brick_t *brick_init(SDL_Renderer *renderer)
{
    brick_t *brick = malloc(sizeof(brick_t));
    if (brick == NULL)
    {
        print_error("Unable to initialize brick");
        return NULL;
    }

    brick->texture = NULL;
    brick->pos = (vec2){0};
    brick->state = BRICK_STATE_DEFAULT;
    brick->bounding_box = (SDL_FRect){
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

void brick_destroy(brick_t *brick)
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

void brick_update(brick_t *brick, input_t *input)
{
    brick->bounding_box.x = brick->pos.x;
    brick->bounding_box.y = brick->pos.y;
}

void brick_draw(brick_t *brick, resource_manager_t *mgr, SDL_Renderer *renderer)
{
    if (brick->state == BRICK_STATE_BROKEN)
    {
        // We do not render broken bricks.
        return;
    }

    SDL_Rect dstrect = {
        .w = BRICK_WIDTH,
        .h = BRICK_HEIGHT,
        .x = brick->pos.x,
        .y = brick->pos.y
    };

    resource_id_t type = (brick->state == BRICK_STATE_DAMAGED) ? TEX_CRACKS : TEX_BRICK;
    SDL_Rect srcrect = TILESET_RECT(type);

    uint8_t nb_tiles = BRICK_WIDTH / TILE_WIDTH;
    
    if (nb_tiles > 1)
    {
        dstrect.w = TILE_WIDTH;
    }

    for (uint i = 0; i < nb_tiles; ++i)
    {
        dstrect.x = brick->pos.x + dstrect.w * i;
        SDL_RenderCopy(renderer, mgr->tileset, &srcrect, &dstrect);
    }
}

void brick_take_damage(brick_t *brick)
{
    if (brick->state == BRICK_STATE_DEFAULT)
    {
        brick->state = BRICK_STATE_DAMAGED;
    }
    else if (brick->state == BRICK_STATE_DAMAGED)
    {
        brick->state = BRICK_STATE_BROKEN;
        brick->bounding_box.w = 0;
        brick->bounding_box.h = 0;
    }
}