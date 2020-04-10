#include "texture_loader.h"


TextureLoader* texture_loader_new(int textures_size) {
    TextureLoader *loader = malloc(sizeof(TextureLoader));

    loader->textures_size = textures_size;
    loader->textures = malloc(textures_size * sizeof(Texture*));
    loader->loaded = 0;

    return loader;
}


void texture_loader_free(TextureLoader *loader) {
    if (!loader) {
        return;
    }

    if (loader->textures) {
        for (int i = 0; i < loader->textures_size; i++) {
            texture_free(loader->textures[i]);
        }
        free(loader->textures);
        loader->textures = NULL;
    }

     free(loader);
}

int texture_loader_load(TextureLoader *loader, SDL_Renderer *renderer, LoaderState loader_state, char **images) {
    if (loader_state != LOADER_TEXTURES) {
        return 0;
    }

    int i = loader->loaded;

    printf("Loading texture %s\n", images[i]);

        SDL_Texture *sdl_texture = texture_new(renderer, images[i]);

        if (!sdl_texture) {
            return -1;
        }

        Texture *texture = malloc(sizeof(Texture));

        loader->textures[i] = texture;
        loader->textures[i]->_tex = sdl_texture;
        SDL_QueryTexture(sdl_texture, NULL, NULL, &texture->width, &texture->height);

        loader->loaded++;

        return 0;
}
