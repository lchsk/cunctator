#include "font_loader.h"


FontLoader* font_loader_new(int fonts_size) {
    FontLoader *loader = calloc(1, sizeof(FontLoader));

    loader->fonts_size = fonts_size;
    loader->fonts = calloc(fonts_size, sizeof(TTF_Font*));
    loader->loaded = 0;

    return loader;
}

void font_loader_free(FontLoader *font_loader) {
    if (!font_loader) {
        return;
    }

    if (font_loader->fonts) {
        // TODO: Free each font

        free(font_loader->fonts);
        font_loader->fonts = NULL;
    }

    free(font_loader);
}

int font_loader_load(FontLoader *font_loader, LoaderState loader_state) {
    if (loader_state != LOADER_FONTS) {
        return 0;
    }

    int i = font_loader->loaded;

    int font_size = font_loader->sizes[i];
    char *path = font_loader->paths[i];

        printf("Loading font %s\n", path);

        TTF_Font *font = TTF_OpenFont(path, font_size);

        if (font == NULL) {
            return -1;
        }

        font_loader->fonts[i] = font;

        font_loader->loaded++;

        return 0;
}
