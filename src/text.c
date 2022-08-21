#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif
#include "text.h"
#include "window.h"

// void draw_text_middle(const char *str, const ui_t *ui)
// {
//     SDL_Surface *surface = TTF_RenderText_Solid(ui->font, str, (SDL_Color) {0x0f, 0x38, 0x0f});
//     SDL_Texture *tex = SDL_CreateTextureFromSurface(ui->renderer, surface);
//     SDL_Rect dest = (SDL_Rect) {
//         .x = WIN_CENTER_X - surface->w / 2,
//         .y = WIN_CENTER_Y - surface->h / 2,
//         .w = surface->w,
//         .h = surface->h
//     };

//     SDL_RenderCopy(ui->renderer, tex, NULL, &dest);
//     SDL_DestroyTexture(tex);
//     SDL_FreeSurface(surface);
// }

void draw_text(const char *str, const ui_t *ui, int x, int y, text_alignment_t alignment)
{
    SDL_Surface *surface = TTF_RenderText_Solid(ui->font, str, (SDL_Color) {0x0f, 0x38, 0x0f});
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ui->renderer, surface);
    SDL_Rect dest = (SDL_Rect) {
        .x = x,
        .y = y,
        .w = surface->w,
        .h = surface->h
    };

    if (alignment & CENTERED_X)
    {
        dest.x = WIN_CENTER_X - surface->w / 2;
    }

    if (alignment & CENTERED_Y)
    {
        dest.y = WIN_CENTER_Y - surface->h / 2;
    }

    SDL_RenderCopy(ui->renderer, tex, NULL, &dest);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surface);
}
