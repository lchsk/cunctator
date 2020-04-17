#ifndef ENGINE_SOUND_LOADER_H
    #define ENGINE_SOUND_LOADER_H

#include <SDL2/SDL_mixer.h>

typedef struct SoundLoader {
    int sounds_size;
    int loaded;
    Mix_Chunk **sounds;
    char **paths;
} SoundLoader;

SoundLoader* sound_loader_new(int size);
void sound_loader_free(SoundLoader* sound_loader);

    #endif /* ENGINE_SOUND_LOADER_H */
