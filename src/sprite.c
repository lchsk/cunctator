#include "sprite.h"

static Sprite *init() {
    Sprite *sprite = malloc(sizeof(Sprite));

    sprite->texture = NULL;
    sprite->zoom = 1.0;
    sprite->position.x = 0;
    sprite->position.y = 0;

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
    if (!sprite) {
        /* TODO: Otherwise seems to crash when using input in debug console */
        return;
    }

        SDL_Rect dest = sprite_dest_rect(sprite);
        SDL_RenderCopy(renderer, sprite->texture->_tex, NULL, &dest);
}
