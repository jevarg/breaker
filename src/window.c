#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif

#include "window.h"
#include "utils.h"

SDL_Window *create_window()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        print_error("Failed to initialize the SDL2 library");
        print_error(SDL_GetError());
        return NULL;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        SDL_Quit();
        print_error("Failed to init PNG support");
        print_error(IMG_GetError());
        return NULL;
    }

    if (TTF_Init() < 0)
    {
        IMG_Quit();
        SDL_Quit();
        print_error("Failed to init TTF support.");
        print_error(TTF_GetError());
        return NULL;
    }

    if (Mix_OpenAudio(11025, AUDIO_U8, 1, 128) < 0)
    {
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        print_error("Failed to open audio mix");
        print_error(Mix_GetError());
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