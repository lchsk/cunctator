#include "sprite.h"

static Sprite *init() {
    Sprite *sprite = calloc(1, sizeof(Sprite));

    sprite->texture = NULL;
    sprite->zoom = 1.0;
    sprite->position.x = 0;
    sprite->position.y = 0;
    sprite->rotation = 0;

    return sprite;
}

Sprite* sprite_new(Texture* texture) {
    Sprite *sprite = init();
    sprite->texture = texture;

    return sprite;
}

Sprite* sprite_new2() {
    return init();
}

void sprite_free(Sprite *sprite) {
    if (!sprite) {
        return;
    }

    // Textures freed by the loader

    free(sprite);
}

SDL_Rect sprite_dest_rect(Sprite *sprite) {
    int w = sprite->texture->width * sprite->zoom;
    int h = sprite->texture->height * sprite->zoom;

    return (SDL_Rect) {sprite->position.x, sprite->position.y, w, h};
}


void sprite_render(Sprite *sprite, SDL_Renderer *renderer) {
    if (!sprite || !sprite->texture || !sprite->texture->_tex) {
        /* TODO: Otherwise seems to crash when using input in debug console */
        return;
    }

    SDL_Rect dest = sprite_dest_rect(sprite);

    if (fabs(sprite->rotation) < 0.0001) {
        SDL_RenderCopy(renderer, sprite->texture->_tex, NULL, &dest);
    } else {
    SDL_RenderCopyEx(renderer,
                     sprite->texture->_tex,
                     NULL,
                     &dest,
                     sprite->rotation,
                     NULL,
                     SDL_FLIP_NONE);
    }
}
