#include "animation.h"


void animation_set_position(Animation *animation, int x, int y) {
    for (int i = 0; i < animation->frames_count; i++) {
        Sprite * sprite = animation->sprites[i];
        sprite->position.x = x;
        sprite->position.y = y;
    }
}


Animation* animation_new(int frames_count) {
    Animation* animation = malloc(sizeof(Animation));

    animation->sprites = malloc(frames_count * sizeof(Sprite*));

    animation->frames_count = frames_count;
    animation->current_frame = 0;
    animation->is_loop = 0;
    animation->is_playing = 0;
    animation->delay_rate = 1.0;
    animation->_since_last_update = 0;

    return animation;
}

void animation_free(Animation *animation) {
    if (!animation) {
        return;
    }

    if (animation->sprites) {
        // TODO: Free each Sprite*

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
