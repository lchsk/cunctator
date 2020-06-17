#ifndef ENGINE_ENTITY_H
    #define ENGINE_ENTITY_H

#include "sprite.h"
#include "animation.h"


typedef struct {
    /* int entity_type; */

    void* properties;

    int animations_total;
    Animation **animations;
    int current_animation;

    Sprite *sprite;

    // TODO: Define required number of rects / different interface
    SDL_Rect rects[1];
    int rects_sz;

    /* SDL_Point position; */
    Pointd position;
} Entity;

Entity *entity_new();
void entity_free(Entity *entity);

/* void entity_set_position(Entity *entity, int x, int y); */
void entity_set_position(Entity *entity, double x, double y);
void entity_set_animations(Entity* entity, int animations_total);
void entity_set_current_animation(Entity* entity, int animation);
void entity_render(Entity* entity, SDL_Renderer *renderer, double delta);

int entity_has_collision(Entity* entity, SDL_Rect* rect);

    #endif /* ENGINE_ENTITY_H */
