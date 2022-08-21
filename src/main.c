#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "ui.h"
#include "input.h"
#include "game.h"
#include "utils.h"

int main()
{
    srand((unsigned) time(NULL));

    ui_t *ui = ui_init();
    if (ui == NULL)
    {
        print_error("Fatal error: Could not create ui!");
        print_error("Exiting...");

        return 1;
    }

    game_start(ui);
    ui_destroy(ui);
}
