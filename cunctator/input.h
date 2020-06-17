#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include <SDL2/SDL.h>

#define _PRESSED_KEYS_SIZE 285

typedef struct Input {
    // Keyboard
    int pressed_keys[_PRESSED_KEYS_SIZE];
    int keys_down[_PRESSED_KEYS_SIZE];
    int keys_up[_PRESSED_KEYS_SIZE];

    // Mouse
    int mouse_x;
    int mouse_y;
    int mouse_left_pressed;
    int mouse_left_down;
    int mouse_left_up;

    SDL_Event event;
    } Input;

Input *input_new();
void input_free(Input *input);

void read_input(Input *input);

#endif /* ENGINE_INPUT_H */
