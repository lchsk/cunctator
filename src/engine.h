#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "enums.h"

#include "texture.h"
#include "sprite.h"
#include "animation.h"
#include "entity.h"
#include "text.h"
#include "console.h"
#include "texture_loader.h"
#include "music_loader.h"
#include "sound_loader.h"
#include "font_loader.h"
#include "loader.h"



typedef struct {
    int requested_fps;
    int width;
    int height;
    char *title;
    int is_running;

    ENGINE_STATE state;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    Entity **entities;

    Loader *preloader;
    Loader *loader;

    int _last_render_time;
    int _delta;
    double _requested_delay;

    Console *console;
} Engine;

Engine *engine_new(int width, int height, char * const title);
void engine_free(Engine *engine);

void engine_clear(Engine *engine);
void engine_present(Engine *engine);


#endif
