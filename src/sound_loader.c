#include "sound_loader.h"


SoundLoader* sound_loader_new(int size) {
    SoundLoader *loader = malloc(sizeof(SoundLoader));

    loader->sounds_size = size;
    loader->sounds = malloc(size * sizeof(Mix_Chunk*));
    loader->loaded = 0;

    return loader;
}

void sound_loader_free(SoundLoader* sound_loader) {
    if (!sound_loader) {
        return;
    }

    if (sound_loader->sounds) {
        // TODO: Free each sound

        free(sound_loader->sounds);
        sound_loader->sounds = NULL;
    }

    free(sound_loader);
}
