#ifndef ENGINE_CONSOLE_H
    #define ENGINE_CONSOLE_H

#include "text.h"

typedef struct Console {
    int is_visible;
    char input[100];
    Text *text;
    TTF_Font *font;

    SDL_Rect rect;
} Console;

Console *console_new(int width, int height);
void console_free(Console *console);

int console_init(Console *console);

void console_render(Console *console, SDL_Renderer *renderer);
void console_input(Console *console, SDL_Renderer *renderer, int key);
void console_reset(Console *console);

    #endif /* ENGINE_CONSOLE_H */
