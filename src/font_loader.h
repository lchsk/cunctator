#ifndef ENGINE_FONT_LOADER_H
    #define ENGINE_FONT_LOADER_H

#include <SDL2/SDL_ttf.h>

#include "enums.h"

typedef struct FontLoader {
    int fonts_size;
    int loaded;
    TTF_Font **fonts;
} FontLoader;

FontLoader* font_loader_new(int fonts_size);
void font_loader_free(FontLoader *font_loader);

int font_loader_load(FontLoader *font_loader, LoaderState loader_state, char **fonts,
                     int *font_sizes);

    #endif /* ENGINE_FONT_LOADER_H */
