#include "entity.h"

Entity *entity_new(Sprite *sprite) {
    Entity *entity = malloc(sizeof(Entity));

    entity->sprite = sprite;

    return entity;
}

void entity_free(Entity *entity) {
    if (!entity) {
        return;
    }

    // TODO: Free animations, animation

    free(entity);
}


void entity_set_position(Entity *entity, int x, int y) {
    entity->position.x = x;
    entity->position.y = y;

    for (int i = 0; i < entity->animations_total; i++) {
        animation_set_position(entity->animations[i], x, y);
    }
}

void entity_set_animations(Entity* entity, int animations_total) {
    entity->animations_total = animations_total;

    entity->animations = malloc(animations_total * sizeof(Animation*));

    entity->current_animation = 0;
}

void entity_set_current_animation(Entity* entity, int animation) {
    entity->current_animation = animation;
}

void entity_render(Entity* entity, SDL_Renderer *renderer, double delta) {
    if (entity->current_animation < 0 || entity->current_animation >= entity->animations_total) {
        return;
    }

    Animation *current = entity->animations[entity->current_animation];

    animation_render(current, renderer, delta);
}
