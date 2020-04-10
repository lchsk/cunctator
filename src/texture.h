#ifndef ENGINE_TEXTURE_H
    #define ENGINE_TEXTURE_H

#include <SDL2/SDL.h>

typedef struct Texture {
    SDL_Texture *_tex;
    int width;
    int height;
} Texture;

SDL_Texture* texture_new(SDL_Renderer *renderer, char const * path);
void texture_free(Texture *texture);

    #endif /* ENGINE_TEXTURE_H */
