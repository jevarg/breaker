#include <SDL2/SDL.h>
#include <stdio.h>
#include <unistd.h>

#include "ui.h"
#include "input.h"

int main()
{
    t_ui *ui = ui_init();

    while (ui->input->mouse_pos.x <= 700)
    {
        SDL_PumpEvents();
        input_update(ui->input);

        printf("(%d, %d)\n", ui->input->mouse_pos.x, ui->input->mouse_pos.y);
        SDL_Delay(1000 / 30);
    }

    ui_destroy(ui);
}
