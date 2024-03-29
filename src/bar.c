#include <stdlib.h>
#include "bar.h"
#include "utils.h"

bar_t *bar_init(SDL_Renderer *renderer)
{
    bar_t *bar = malloc(sizeof(bar_t));
    if (bar == NULL)
    {
        print_error("Unable to initialize bar");
        return NULL;
    }

    bar->texture = NULL;
    bar->force = 0;
    bar->pos = (vec2) {0};
    bar->bounding_box = (SDL_FRect) {
        .x = 0,
        .y = 0,
        .w = BAR_WIDTH,
        .h = BAR_HEIGHT
    };

    return bar;
}

void bar_destroy(bar_t *bar)
{
    if (bar == NULL)
    {
        return;
    }

    if (bar->texture != NULL)
    {
        SDL_DestroyTexture(bar->texture);
    }

    free(bar);
}

void bar_update(bar_t *bar, input_t *input)
{
    bar->pos.x = (input->mouse_pos.x - BAR_WIDTH / 2);

    bar->bounding_box.x = bar->pos.x;
    bar->bounding_box.y = bar->pos.y;

    bar->force = SDL_max(1, abs(input->mouse_delta.x) / 2);
}

void bar_draw(bar_t *bar, resource_manager_t *mgr, SDL_Renderer *renderer)
{
    SDL_Rect dstrect = {
        .h = BAR_HEIGHT,
        .w = BAR_WIDTH,
        .x = bar->pos.x,
        .y = bar->pos.y
    };

    SDL_Rect src_rect = TILESET_RECT(TEX_BAR_LEFT);

    if (BAR_WIDTH > TILE_WIDTH)
    {
        dstrect.w = TILE_WIDTH;
        uint8_t nb_tiles = (BAR_WIDTH / TILE_WIDTH);

        for (uint8_t i = 0; i < nb_tiles; ++i)
        {
            if (!i)
            {
                src_rect.x = (TILE_WIDTH * TEX_BAR_LEFT);
            }
            else if (i + 1 == nb_tiles)
            {
                src_rect.x = (TILE_WIDTH * TEX_BAR_RIGHT);
            }
            else
            {
                src_rect.x = (TILE_WIDTH * TEX_BAR_BODY);
            }

            dstrect.x = bar->pos.x + (dstrect.w * i);

            SDL_RenderCopy(renderer, mgr->tileset, &src_rect, &dstrect);
        }
    }
}
