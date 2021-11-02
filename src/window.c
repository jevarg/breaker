#include <SDL2_image/SDL_image.h>

#include "window.h"
#include "utils.h"

SDL_Window *create_window()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        print_error("Failed to initialize the SDL2 library");
        return NULL;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        print_error("Failed to init PNG support");
        return NULL;
    }

    SDL_Window *win = SDL_CreateWindow(WIN_TITLE,
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WIN_WIDTH, WIN_HEIGHT,
                                       0);

    return win;
}