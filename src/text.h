#pragma once

#include "ui.h"

typedef enum text_alignment_t
{
    CENTERED_X = 0b00000001,
    CENTERED_Y = 0b00000010,
} text_alignment_t;

void draw_text(const char *str, const ui_t *ui, int x, int y, text_alignment_t alignment);
