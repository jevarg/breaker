#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <unistd.h>

#include "ui.h"
#include "input.h"
#include "game.h"
#include "utils.h"

int main()
{
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
