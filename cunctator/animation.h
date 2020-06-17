#ifndef ENGINE_ANIMATION_H
    #define ENGINE_ANIMATION_H

#include "sprite.h"
#include "texture_loader.h"

typedef struct Animation {
    int frames_count;
    int current_frame;
    int is_loop;
    int is_playing;
    Sprite **sprites;
    double delay_rate;

    double _since_last_update;
} Animation;

Animation* animation_new(int frames_count);
void animation_free(Animation *animation);

void animation_set_textures(Animation *animation, TextureLoader *loader, int frames_count, ...);
void animation_set_position(Animation *animation, int x, int y);
void animation_set_zoom(Animation *animation, double zoom);
void animation_update(Animation *animation, double delta);
void animation_render(Animation *animation, SDL_Renderer* renderer, double delta);

#endif /* ENGINE_ANIMATION_H */
