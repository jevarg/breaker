#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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
        SDL_Quit();
        print_error("Failed to init PNG support");
        return NULL;
    }

    if (TTF_Init() < 0)
    {
        IMG_Quit();
        SDL_Quit();
        print_error("Failed to init TTF support");
        return NULL;
    }

    SDL_Window *win = SDL_CreateWindow(WIN_TITLE,
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WIN_WIDTH, WIN_HEIGHT,
                                       0);

    return win;
}

void destroy_window(SDL_Window *win)
{
    if (win != NULL)
    {
        SDL_DestroyWindow(win);
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}