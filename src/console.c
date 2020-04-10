#include "console.h"

static int is_key_allowed(int key);

Console *console_new(int width, int height) {
    Console *console = malloc(sizeof(Console));

    console->is_visible = 0;
    console->rect.x = 0;
    console->rect.y = 0;
    console->rect.w = width;
    console->rect.h = height * 0.7;

    strcpy(console->input, "");

    return console;
}

void console_free(Console *console) {
    if (!console) {
        return;
    }

    if (console->text) {
        text_free(console->text);
        console->text = NULL;
    }

    // Free TTF Font
}

int console_init(Console *console) {
    console->font = TTF_OpenFont("./FreeSans.ttf", 18);
    if (console->font == NULL) {
        return -1;
    }

    console->text = text_new(console->font);

    return 0;
}

void console_render(Console *console, SDL_Renderer* renderer) {
    if (!console->is_visible) {
        return;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_RenderFillRect(renderer, &console->rect);

    if (strlen(console->input) > 0) {
        sprite_render(console->text->sprite, renderer);
    }
}

void console_input(Console* console, SDL_Renderer *renderer, int key) {
    if (!console->is_visible) {
        return;
    }

    if (!is_key_allowed(key)) {
        return;
    }

    int len = strlen(console->input);

    console->input[len] = key;
    console->input[len + 1] = '\0';

    text_set(console->text, renderer, console->input);
}

void console_reset(Console *console) {
    strcpy(console->input, "");
}

static int is_key_allowed(int key) {
    if (key == 32) {
        return 1;
    }

    if (key == 61) {
        return 1;
    }

    if (key >= 48 && key <= 57) {
        return 1;
    }

    if (key >= 97 && key <= 122) {
        return 1;
    }

    return 0;
}
