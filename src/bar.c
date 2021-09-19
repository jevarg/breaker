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
    bar->x = 0;
    bar->y = 0;

    SDL_Surface *s = SDL_CreateRGBSurface(0, BAR_WIDTH, BAR_HEIGHT, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
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
    bar->x = input->mouse_pos.x;
}

void bar_draw(t_bar *bar, SDL_Renderer *renderer)
{
    SDL_Rect rect = {
        .h = BAR_HEIGHT,
        .w = BAR_WIDTH,
        .x = bar->x,
        .y = bar->y
    };

    SDL_RenderCopy(renderer, bar->texture, NULL, &rect);
}
