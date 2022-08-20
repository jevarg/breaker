#include "utils.h"
#include "ui.h"
#include "window.h"

ui_t *ui_init()
{
    ui_t *ui;

    ui = calloc(1, sizeof(ui_t));
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

    ui->renderer = SDL_CreateRenderer(ui->win, -1, SDL_RENDERER_ACCELERATED);
    if (ui->renderer == NULL)
    {
        print_error("Failed to get renderer from the window");
        ui_destroy(ui);

        return NULL;
    }

    ui->font = TTF_OpenFont("../gamegirl_classic.ttf", 24);
    if (ui->font == NULL)
    {
        print_error("Failed to load font");
        ui_destroy(ui);

        return NULL;
    }

    ui->input = calloc(1, sizeof(input_t));
    if (ui->input == NULL)
    {
        ui_destroy(ui);
        return NULL;
    }

    SDL_SetRenderDrawColor(ui->renderer, 155, 188, 15, 255);
    ui->input->needs_exit = SDL_FALSE;
    ui->input->kbd_state = SDL_GetKeyboardState(NULL);
    ui->input->mouse_pos.x = 0;
    ui->input->mouse_pos.y = 0;

    return ui;
}

void ui_destroy(ui_t *ui)
{
    if (ui == NULL)
    {
        return;
    }

    if (ui->input != NULL)
    {
        free(ui->input);
    }

    if (ui->renderer != NULL)
    {
        SDL_DestroyRenderer(ui->renderer);
    }

    if (ui->font != NULL)
    {
        TTF_CloseFont(ui->font);
    }

    if (ui->win != NULL)
    {
        destroy_window(ui->win);
    }

    free(ui);
}