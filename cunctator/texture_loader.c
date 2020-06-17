#include "texture_loader.h"


TextureLoader* texture_loader_new(int textures_size) {
    TextureLoader *loader = calloc(1, sizeof(TextureLoader));

    loader->textures_size = textures_size;
    loader->textures = calloc(textures_size, sizeof(Texture*));
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

int texture_loader_load(TextureLoader *loader, SDL_Renderer *renderer, LoaderState loader_state) {
    if (!loader) {
        return 0;
    }

    if (loader_state != LOADER_TEXTURES) {
        return 0;
    }

    int i = loader->loaded;

    char *path = loader->paths[i];

    #ifdef DEBUG_LOG_LOADING
    LOGFMT("Loading texture %s\n", path);
    #endif

        SDL_Texture *sdl_texture = texture_new(renderer, path);

        if (!sdl_texture) {
            return -1;
        }

        Texture *texture = calloc(1, sizeof(Texture));

        loader->textures[i] = texture;
        loader->textures[i]->_tex = sdl_texture;
        SDL_QueryTexture(sdl_texture, NULL, NULL, &texture->width, &texture->height);

        loader->loaded++;

        return 0;
}
