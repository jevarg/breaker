#include "utils.h"
#include "ui.h"
#include "window.h"

t_ui *ui_init()
{
    t_ui *ui;

    ui = malloc(sizeof(t_ui));
    if (ui == NULL)
    {
        return NULL;
    }

    ui->win = create_window();
    if (ui->win == NULL)
    {
        print_error("Could not create window!");
        ui_destroy(ui);

        return NULL;
    }

    ui->renderer = SDL_CreateRenderer(ui->win, -1, 0);
    if (ui->renderer == NULL)
    {
        print_error("Failed to get renderer from the window");
        ui_destroy(ui);

        return NULL;
    }

    ui->input = malloc(sizeof(t_input));
    if (ui->input == NULL)
    {
        ui_destroy(ui);
        return NULL;
    }

    ui->input->mouse_pos.x = 0;
    ui->input->mouse_pos.y = 0;

    return ui;
}

void ui_destroy(t_ui *ui)
{
    if (ui == NULL)
    {
        return;
    }

    if (ui->renderer != NULL)
    {
        SDL_DestroyRenderer(ui->renderer);
    }

    if (ui->win != NULL)
    {
        SDL_DestroyWindow(ui->win);
    }

    if (ui->input != NULL)
    {
        free(ui->input);
    }

    free(ui);
    SDL_Quit();
}