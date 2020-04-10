#include "music_loader.h"


MusicLoader* music_loader_new(int size) {
    MusicLoader *loader = malloc(sizeof(MusicLoader));

    loader->music_size = size;
    loader->music = malloc(size * sizeof(Mix_Music*));
    loader->loaded = 0;

    return loader;
}

void music_loader_free(MusicLoader* music_loader) {
    if (!music_loader) {
        return;
    }

    if (music_loader->music) {
        // TODO: Free each music item

        free(music_loader->music);
        music_loader->music = NULL;
    }

    free(music_loader);
}
