#include <SDL2/SDL.h>
#include <stdio.h>
#include <unistd.h>

#include "ui.h"
#include "input.h"
#include "game.h"

int main()
{
    t_ui *ui = ui_init();

    game_start(ui);
    ui_destroy(ui);
}
