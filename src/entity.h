#ifndef ENGINE_ENTITY_H
    #define ENGINE_ENTITY_H

#include "sprite.h"
#include "animation.h"

typedef struct {
    int entity_type;

    int animations_total;
    Animation **animations;
    int current_animation;

    Animation *animation;
    Sprite *sprite;

    SDL_Point position;
} Entity;

Entity *entity_new(Sprite *sprite);
void entity_free(Entity *entity);

void entity_set_position(Entity *entity, int x, int y);
void entity_set_animations(Entity* entity, int animations_total);
void entity_set_current_animation(Entity* entity, int animation);
void entity_render(Entity* entity, SDL_Renderer *renderer, double delta);

    #endif /* ENGINE_ENTITY_H */
