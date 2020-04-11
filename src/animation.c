#include "animation.h"


void animation_set_position(Animation *animation, int x, int y) {
    for (int i = 0; i < animation->frames_count; i++) {
        Sprite * sprite = animation->sprites[i];
        sprite->position.x = x;
        sprite->position.y = y;
    }
}


Animation* animation_new(int frames_count) {
    Animation* animation = calloc(1, sizeof(Animation));

    animation->sprites = calloc(frames_count, sizeof(Sprite*));

    for (int i = 0; i < frames_count; i++) {
        animation->sprites[i] = sprite_new2();
    }

    animation->frames_count = frames_count;
    animation->current_frame = 0;
    animation->is_loop = 1;
    animation->is_playing = 1;
    animation->delay_rate = 1.0;
    animation->_since_last_update = 0;

    return animation;
}

void animation_free(Animation *animation) {
    if (!animation) {
        return;
    }

    if (animation->sprites) {
        for (int i = 0; i < animation->frames_count; i++) {
            if (animation->sprites[i]) {
                sprite_free(animation->sprites[i]);
                animation->sprites[i] = NULL;
            }
        }

        free(animation->sprites);
        animation->sprites = NULL;
    }

    free(animation);
}

void animation_update(Animation *animation, double delta) {
   if (!animation->is_playing) {
       return;
   }

   animation->_since_last_update += delta;
   int move_frames = 1;

   if (animation->_since_last_update > delta * animation->delay_rate) {
       move_frames = 1;
   } else {
       move_frames = 0;
   }

   if (!move_frames) {
       return;
   }

   animation->_since_last_update = 0;

   if (animation->current_frame < animation->frames_count) {
       animation->current_frame++;
   }

   if (animation->is_loop && animation->current_frame == animation->frames_count) {
       animation->current_frame = 0;
   }
}

void animation_render(Animation *animation, SDL_Renderer* renderer, double delta) {
    animation_update(animation, delta);

    sprite_render(animation->sprites[animation->current_frame], renderer);
}

void animation_set_textures(Animation *animation, TextureLoader *loader, int frames_count, ...) {
    va_list p;
    va_start(p, frames_count);

    for (int i = 0; i < frames_count; i++) {
        int texture = va_arg(p, int);
        animation->sprites[i]->texture = loader->textures[texture];
    }

    va_end(p);
}
