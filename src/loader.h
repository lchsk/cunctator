#ifndef ENGINE_LOADER_H
    #define ENGINE_LOADER_H

#include "texture_loader.h"
#include "font_loader.h"
#include "music_loader.h"
#include "sound_loader.h"
#include "enums.h"

typedef struct Loader {
    TextureLoader *texture_loader;
    FontLoader *font_loader;
    MusicLoader *music_loader;
    SoundLoader *sound_loader;

    LoaderState state;

    int total_loaded;
    int total_to_load;
} Loader;

Loader* loader_new();
void loader_free(Loader* loader);


void loader_update(Loader *loader);
int sound_loader_load(Loader *loader, char **sounds);
int music_loader_load(Loader *loader, char **music);

ENGINE_STATE check_if_loading_finished(Loader *loader, ENGINE_STATE engine_state);

    #endif /* ENGINE_LOADER_H */
