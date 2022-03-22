#pragma once

#include <SDL2/SDL.h>

#define WIN_WIDTH 768
#define WIN_HEIGHT 640
#define WIN_H_CENTER (WIN_WIDTH / 2)
#define WIN_V_CENTER (WIN_HEIGHT / 2)
#define WIN_TITLE "Breakout" // TODO: Change this boring name...

SDL_Window *create_window();