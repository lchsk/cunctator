#include "text.h"



Text* text_new(TTF_Font* font) {
    Text* t = malloc(sizeof(Text));

    t->sprite = NULL;
    t->font = font;
    t->color = (SDL_Color) {255, 255, 255, 255};

    return t;
}

void text_free(Text *text) {
    if (!text) {
        return;
    }

    // Free TTF Font

    if (text->sprite) {
        sprite_free(text->sprite);
        text->sprite = NULL;
    }

    free(text);
}


int text_set(Text* text, SDL_Renderer* renderer, char *string) {
    text->string = string;

    SDL_Surface *surf = TTF_RenderText_Blended(text->font, text->string, text->color);

    if (surf == NULL) {
        return -1;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

    if (tex == NULL) {
        return -1;
    }

    SDL_FreeSurface(surf);

    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);

    if (text->sprite == NULL) {
        Texture *texture = malloc(sizeof(Texture));
        texture->_tex = tex;
        texture->width = w;
        texture->height = h;

        text->sprite = sprite_new(texture);
    } else {
        SDL_DestroyTexture(text->sprite->texture->_tex);

        text->sprite->texture->_tex = tex;
        text->sprite->texture->width = w;
        text->sprite->texture->height = h;
    }

    return 0;
}
