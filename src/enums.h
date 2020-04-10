#ifndef ENGINE_ENUMS_H
    #define ENGINE_ENUMS_H


typedef enum {
    ENGINE_INITIAL,
    ENGINE_PRELOADING,
    ENGINE_LOADING,
    ENGINE_RUNNING,
} ENGINE_STATE;

typedef enum LoaderState {
    LOADER_TEXTURES,
    LOADER_FONTS,
    LOADER_MUSIC,
    LOADER_SOUNDS,
    LOADER_FINISHED,
} LoaderState;


    #endif /* ENGINE_ENUMS_H */
