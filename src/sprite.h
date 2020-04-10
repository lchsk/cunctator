#ifndef ENGINE_SPRITE_H
    #define ENGINE_SPRITE_H

#include <SDL2/SDL.h>

#include "texture.h"

typedef struct {
    Texture *texture;
    double zoom;
    SDL_Point position;
} Sprite;

Sprite* sprite_new(Texture* texture);
void sprite_free(Sprite *sprite);

SDL_Rect sprite_dest_rect(Sprite *sprite);

void sprite_render(Sprite *sprite, SDL_Renderer *renderer);

    #endif /* ENGINE_SPRITE_H */
