#include "engine.h"

static void engine_calculate_delta(Engine *engine);

Engine *engine_new(int width, int height, char * const title) {
    Engine *engine = malloc(sizeof(Engine));
    engine->width = width;
    engine->height = height;
    engine->title = title;
    engine->requested_fps = 60;
    engine->_requested_delay = 1000 / engine->requested_fps;
    engine->state = ENGINE_INITIAL;

    Uint32 init_flags =
        SDL_INIT_VIDEO
        | SDL_INIT_TIMER
        | SDL_INIT_AUDIO
        | SDL_INIT_EVENTS;

    if (SDL_Init(init_flags) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return NULL;
    }

    TTF_Init();

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return NULL;
    }

    engine->window = SDL_CreateWindow(title, 0, 0,
                                      width, height,
                                      0);

    if (engine->window == NULL) {
        printf("Window creation failed\n");
        return NULL;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    engine->renderer = SDL_CreateRenderer(engine->window, -1, render_flags);

    if (engine->renderer == NULL) {
        printf("Renderer creation failed\n");
        return NULL;
    }

    engine->console = console_new(width, height);
    console_init(engine->console);

    engine->is_running = 1;

    return engine;
}

void engine_free(Engine *engine) {
    if (!engine) {
        return;
    }

    if (engine->console) {
        console_free(engine->console);
        engine->console = NULL;
    }

    if (engine->renderer) {
        SDL_DestroyRenderer(engine->renderer);
        engine->renderer = NULL;
    }

    if (engine->window) {
        SDL_DestroyWindow(engine->window);
        engine->window = NULL;
    }

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    if (engine) {
        free(engine);
    }
}

void engine_clear(Engine *engine) {
    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 255);
    SDL_RenderClear(engine->renderer);

    if (engine->console->is_visible) {
        SDL_SetRenderDrawBlendMode(engine->renderer, SDL_BLENDMODE_BLEND);
    } else {
        SDL_SetRenderDrawBlendMode(engine->renderer, SDL_BLENDMODE_NONE);
    }
}

void engine_present(Engine *engine) {
    SDL_RenderPresent(engine->renderer);

    engine_calculate_delta(engine);
}

static void engine_calculate_delta(Engine *engine) {
  unsigned int total_elapsed = SDL_GetTicks();

  if (total_elapsed > engine->_last_render_time) {
    engine->_delta = total_elapsed - engine->_last_render_time;
    engine->_last_render_time = total_elapsed;
  }
}
