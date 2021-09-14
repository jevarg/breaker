#include "window.h"
#include "utils.h"

SDL_Window *create_window()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        print_error("Failed to initialize the SDL2 library");
        return NULL;
    }

    SDL_Window *win = SDL_CreateWindow(WIN_TITLE,
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WIN_WIDTH, WIN_HEIGHT,
                                       0);

    return win;
}