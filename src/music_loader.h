#ifndef ENGINE_MUSIC_LOADER_H
    #define ENGINE_MUSIC_LOADER_H

#include <SDL2/SDL_mixer.h>

typedef struct MusicLoader {
    int music_size;
    int loaded;
    Mix_Music **music;
} MusicLoader;

MusicLoader* music_loader_new(int size);
void music_loader_free(MusicLoader* music_loader);

    #endif /* ENGINE_MUSIC_LOADER_H */
