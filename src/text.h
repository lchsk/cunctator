#ifndef ENGINE_TEXT_H
    #define ENGINE_TEXT_H

#include <SDL2/SDL_ttf.h>

#include "sprite.h"

typedef struct Text {
    TTF_Font *font;
    char *string;
    SDL_Color color;

    Sprite *sprite;
} Text;

Text* text_new(TTF_Font* font);
void text_free(Text *text);
int text_set(Text* text, SDL_Renderer* renderer, char *string);

    #endif /* ENGINE_TEXT_H */
