#include "sprite.h"


Sprite* sprite_new(Texture* texture) {
    Sprite *sprite = malloc(sizeof(Sprite));

    sprite->texture = texture;
    sprite->zoom = 1.0;
    sprite->position.x = 0;
    sprite->position.y = 0;

    return sprite;
}

void sprite_free(Sprite *sprite) {
    if (!sprite) {
        return;
    }

    if (sprite->texture) {
        texture_free(sprite->texture);
        sprite->texture = NULL;
    }

    free(sprite);
}

SDL_Rect sprite_dest_rect(Sprite *sprite) {
    int w = sprite->texture->width * sprite->zoom;
    int h = sprite->texture->height * sprite->zoom;

    return (SDL_Rect) {sprite->position.x, sprite->position.y, w, h};
}


void sprite_render(Sprite *sprite, SDL_Renderer *renderer) {
    if (!sprite) {
        /* TODO: Otherwise seems to crash when using input in debug console */
        return;
    }

        SDL_Rect dest = sprite_dest_rect(sprite);
        SDL_RenderCopy(renderer, sprite->texture->_tex, NULL, &dest);
}
