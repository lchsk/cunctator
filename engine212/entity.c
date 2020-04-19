#include "entity.h"

Entity *entity_new() {
    Entity *entity = calloc(1, sizeof(Entity));

    entity->animations = NULL;
    entity->sprite = NULL;
    entity->current_animation = 0;
    entity->animations_total = 0;

    entity->position.x = 0;
    entity->position.y = 0;

    // Collisions
    entity->rects_sz = 0;

    return entity;
}

void entity_free(Entity *entity) {
    if (!entity) {
        return;
    }

    for (int i = 0; i < entity->animations_total; i++) {
        if (entity->animations[i]) {
            animation_free(entity->animations[i]);
            entity->animations[i] = NULL;
        }
    }

    if (entity->sprite) {
        sprite_free(entity->sprite);
        entity->sprite = NULL;
    }

    free(entity);
}


/* void entity_set_position(Entity *entity, int x, int y) { */
void entity_set_position(Entity *entity, double x, double y) {
    entity->position.x = x;
    entity->position.y = y;

    entity->rects[0].x = x;
    entity->rects[0].y = y;

    if (entity->sprite) {
        Sprite* sprite = entity->sprite;
        sprite->position.x = x;
        sprite->position.y = y;
    } else if (entity->animations) {
        entity->position.x = x;
        entity->position.y = y;

        for (int i = 0; i < entity->animations_total; i++) {
            animation_set_position(entity->animations[i], x, y);
        }
    }
}

void entity_set_animations(Entity* entity, int animations_total) {
    entity->animations_total = animations_total;

    entity->animations = calloc(animations_total, sizeof(Animation*));

    entity->current_animation = 0;
}

void entity_set_current_animation(Entity* entity, int animation) {
    entity->current_animation = animation;
}

void entity_render(Entity* entity, SDL_Renderer *renderer, double delta) {
    if (entity->sprite) {
        sprite_render(entity->sprite, renderer);
    } else if (entity->animations) {
        if (entity->current_animation < 0 || entity->current_animation >= entity->animations_total) {
            return;
        }

        Animation *current = entity->animations[entity->current_animation];

        animation_render(current, renderer, delta);
    }

#ifdef DEBUG_COLLISIONS
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

    SDL_RenderDrawRects(renderer, entity->rects, entity->rects_sz);
#endif

}

int entity_has_collision(Entity* entity, SDL_Rect* rect) {
    for (int i = 0; i < entity->rects_sz; i++) {
        if (SDL_HasIntersection(&entity->rects[i], rect)) {
            return 1;
        }
    }

    return 0;
}
