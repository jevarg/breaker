#include <stdlib.h>
#include "bar.h"
#include "utils.h"

t_bar *bar_init(SDL_Renderer *renderer)
{
    t_bar *bar = malloc(sizeof(t_bar));
    if (bar == NULL)
    {
        print_error("Unable to initialize bar");
        return NULL;
    }

    bar->texture = NULL;
    bar->force = 0;
    bar->pos = (vec2) {0};
    bar->bounding_box = (SDL_Rect) {
        .x = 0,
        .y = 0,
        .w = BAR_WIDTH,
        .h = BAR_HEIGHT
    };

    SDL_Surface *s = SDL_CreateRGBSurface(0, bar->bounding_box.w, bar->bounding_box.h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    if (s == NULL)
    {
        print_error("Unable to create bar surface!");
        bar_destroy(bar);

        return NULL;
    }

    SDL_FillRect(s, NULL, 0xff0000ff);
    bar->texture = SDL_CreateTextureFromSurface(renderer, s);
    if (bar->texture == NULL)
    {
        print_error("Unable to create bar texture");
        bar_destroy(bar);

        return NULL;
    }

    return bar;
}

void bar_destroy(t_bar *bar)
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

void bar_update(t_bar *bar, t_input *input)
{
    bar->pos.x = (input->mouse_pos.x - BAR_WIDTH / 2);

    bar->bounding_box.x = bar->pos.x;
    bar->bounding_box.y = bar->pos.y;

    bar->force = SDL_max(1, abs(input->mouse_delta.x));
}

void bar_draw(t_bar *bar, SDL_Renderer *renderer)
{
    SDL_Rect rect = {
        .h = BAR_HEIGHT,
        .w = BAR_WIDTH,
        .x = bar->pos.x,
        .y = bar->pos.y
    };

    SDL_RenderCopy(renderer, bar->texture, NULL, &rect);
}
