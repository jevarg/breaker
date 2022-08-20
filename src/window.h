#pragma once

#include <SDL2/SDL.h>

#define WIN_WIDTH 768
#define WIN_HEIGHT 640
#define WIN_CENTER_X (WIN_WIDTH / 2)
#define WIN_CENTER_Y (WIN_HEIGHT / 2)
#define WIN_TITLE "Breakout" // TODO: Change this boring name...

SDL_Window *create_window();
void destroy_window(SDL_Window *win);