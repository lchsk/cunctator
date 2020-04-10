#ifndef ENGINE_TEXTURE_LOADER_H
    #define ENGINE_TEXTURE_LOADER_H

#include "enums.h"
#include "texture.h"

typedef struct TextureLoader {
    int textures_size;
    int loaded;
    Texture **textures;

} TextureLoader;

TextureLoader* texture_loader_new(int textures_size);
void texture_loader_free(TextureLoader *loader);

int texture_loader_load(TextureLoader *loader, SDL_Renderer *renderer, LoaderState loader_state, char **images);

    #endif /* ENGINE_TEXTURE_LOADER_H */
