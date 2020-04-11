#include "loader.h"



Loader* loader_new(int textures_count, int fonts_count, int music_count, int sounds_count) {
    Loader *loader = malloc(sizeof(Loader));

    loader->texture_loader = textures_count > 0 ? texture_loader_new(textures_count) : NULL;
    loader->font_loader = fonts_count > 0 ? font_loader_new(fonts_count) : NULL;
    loader->music_loader = music_count > 0 ? music_loader_new(music_count) : NULL;
    loader->sound_loader = sounds_count > 0 ? sound_loader_new(sounds_count) : NULL;

    loader->total_loaded = 0;
    loader->total_to_load = 0;
    loader->state = LOADER_TEXTURES;

    return loader;
}

void loader_free(Loader* loader) {
    if (!loader) {
        return;
    }

    if (loader->texture_loader) {
        texture_loader_free(loader->texture_loader);
        loader->texture_loader = NULL;
    }

    if (loader->font_loader) {
        font_loader_free(loader->font_loader);
        loader->font_loader = NULL;
    }

    if (loader->music_loader) {
        music_loader_free(loader->music_loader);
        loader->music_loader = NULL;
    }

    if (loader->music_loader) {
        music_loader_free(loader->music_loader);
        loader->music_loader = NULL;
    }

    free(loader);
}

void loader_update(Loader *loader) {
    TextureLoader* texture_loader = loader->texture_loader;
    FontLoader* font_loader = loader->font_loader;
    MusicLoader* music_loader = loader->music_loader;
    SoundLoader* sound_loader = loader->sound_loader;

    int texture_loaded = 0, texture_size = 0;
    int font_loaded = 0, font_size = 0;
    int music_loaded = 0, music_size = 0;
    int sound_loaded = 0, sound_size = 0;

    if (texture_loader == NULL) {
        loader->state = LOADER_FONTS;
    } else {
        texture_loaded = texture_loader->loaded;
        texture_size = texture_loader->textures_size;
    }

    if (font_loader == NULL) {
        loader->state = LOADER_MUSIC;
    } else {
        font_loaded = font_loader->loaded;
        font_size = font_loader->fonts_size;
    }

    if (music_loader == NULL) {
        loader->state = LOADER_SOUNDS;
    } else {
        music_loaded = music_loader->loaded;
        music_size = music_loader->music_size;
    }

    if (sound_loader == NULL) {
        loader->state = LOADER_FINISHED;
    } else {
        sound_loaded = sound_loader->loaded;
        sound_size = sound_loader->sounds_size;
    }

    loader->total_to_load = texture_size + font_size + music_size + sound_size;
    loader->total_loaded = texture_loaded + font_loaded + music_loaded + sound_loaded;

    // Switch state: TEXTURES -> FONTS -> MUSIC -> SOUNDS
    if (loader->state == LOADER_TEXTURES && texture_loaded == texture_size) {
        loader->state = LOADER_FONTS;
    }

    if (loader->state == LOADER_FONTS && font_loaded == font_size) {
        loader->state = LOADER_MUSIC;
    }

    if (loader->state == LOADER_MUSIC && music_loaded == music_size) {
        loader->state = LOADER_SOUNDS;
    }

    if (loader->state == LOADER_SOUNDS && sound_loaded == sound_size) {
        loader->state = LOADER_FINISHED;
    }
}

int sound_loader_load(Loader *loader) {
    if (loader->state != LOADER_SOUNDS) {
        return 0;
    }

    SoundLoader *sound_loader = loader->sound_loader;

    int i = sound_loader->loaded;

    char *path = sound_loader->paths[i];

    printf("Loading sound %s\n", path);

    sound_loader->sounds[i] = Mix_LoadWAV(path);

    if (sound_loader->sounds[i] == NULL) {
        return -1;
    }

    sound_loader->loaded++;

    return 0;
}

int music_loader_load(Loader *loader) {
    if (loader->state != LOADER_MUSIC) {
        return 0;
    }

    MusicLoader *music_loader = loader->music_loader;

    int i = music_loader->loaded;

    char *path = music_loader->paths[i];

    printf("Loading music %s\n", path);

    music_loader->music[i] = Mix_LoadMUS(path);

    if (music_loader->music[i] == NULL) {
        return -1;
    }

    music_loader->loaded++;

    return 0;
}

ENGINE_STATE check_if_loading_finished(Loader *loader, ENGINE_STATE engine_state) {
    FontLoader *font_loader = loader->font_loader;
    TextureLoader *texture_loader = loader->texture_loader;
    MusicLoader *music_loader = loader->music_loader;
    SoundLoader *sound_loader = loader->sound_loader;

    int fonts_ok = 0;
    int textures_ok = 0;
    int music_ok = 0;
    int sound_ok = 0;

    if (font_loader == NULL) {
        fonts_ok = 1;
    } else {
        fonts_ok = font_loader->loaded == font_loader->fonts_size;
    }

    if (texture_loader == NULL) {
        textures_ok = 1;
    } else {
        textures_ok = texture_loader->loaded == texture_loader->textures_size;
    }

    if (music_loader == NULL) {
        music_ok = 1;
    } else {
        music_ok = music_loader->loaded == music_loader->music_size;
    }

    if (sound_loader == NULL) {
        sound_ok = 1;
    } else {
        sound_ok = sound_loader->loaded == sound_loader->sounds_size;
    }

    printf("%d %d %d %d \n", fonts_ok, textures_ok, music_ok, sound_ok);

    if (fonts_ok && textures_ok && music_ok && sound_ok) {
        if (engine_state == ENGINE_PRELOADING) {
            /* return ENGINE_LOADING; */
            return ENGINE_LOADING_SCREEN_SETUP;
        } else if (engine_state == ENGINE_LOADING) {
            /* return ENGINE_RUNNING; */
            return ENGINE_GAME_SETUP;
        }
    }

    return engine_state;
}
