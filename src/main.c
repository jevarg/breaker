#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <unistd.h>

#include "ui.h"
#include "input.h"
#include "game.h"

int main()
{
    t_ui *ui = ui_init();

    SDL_Surface *imgSurface = IMG_Load("../test.jpg");
    SDL_Texture *tex = NULL;

    tex = SDL_CreateTextureFromSurface(ui->renderer, imgSurface);

    SDL_FreeSurface(imgSurface);

    game_start(ui);

    ui_destroy(ui);
}
