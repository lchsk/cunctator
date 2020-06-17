#include <SDL2/SDL_image.h>

#include "config.h"
#include "texture.h"


SDL_Texture* texture_new(SDL_Renderer *renderer, char const * path) {
    SDL_Surface *surface = IMG_Load(path);

    if (!surface) {
        LOGFMT("IMG_Load failed for %s\n", path);
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (!texture) {
        LOGFMT("Create texture from surface failed for %s\n", path);
        return NULL;
    }

    SDL_FreeSurface(surface);

    return texture;
}

void texture_free(Texture *texture) {
    if (!texture) {
        return;
    }

    if (texture->_tex) {
        SDL_DestroyTexture(texture->_tex);
        texture->_tex = NULL;
    }

    free(texture);
}
