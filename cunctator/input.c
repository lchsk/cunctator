#include "input.h"

Input *input_new() {
    Input *input = calloc(1, sizeof(Input));

    memset(input->pressed_keys, 0, _PRESSED_KEYS_SIZE * sizeof(int));
    memset(input->keys_down, 0, _PRESSED_KEYS_SIZE * sizeof(int));
    memset(input->keys_up, 0, _PRESSED_KEYS_SIZE * sizeof(int));

    input->mouse_left_pressed = 0;
    input->mouse_left_down = 0;
    input->mouse_left_up = 0;

    return input;
}

void input_free(Input *input) {
    if (!input) {
        return;
    }

    free(input);
}

void read_input(Input *input) {
    memset(input->keys_down, 0, _PRESSED_KEYS_SIZE * sizeof(int));
    memset(input->keys_up, 0, _PRESSED_KEYS_SIZE * sizeof(int));

    input->mouse_left_down = 0;
    input->mouse_left_up = 0;

    SDL_GetMouseState(&input->mouse_x, &input->mouse_y);

    while (SDL_PollEvent(&input->event)) {
        Uint32 event_type = input->event.type;

        if (event_type == SDL_MOUSEBUTTONDOWN) {
            SDL_MouseButtonEvent ev = input->event.button;

            if (ev.button == SDL_BUTTON_LEFT) {
                input->mouse_left_pressed = 1;
                input->mouse_left_down = 1;
                input->mouse_left_up = 0;
            }
        }

        if (event_type == SDL_MOUSEBUTTONUP) {
            SDL_MouseButtonEvent ev = input->event.button;

            if (ev.button == SDL_BUTTON_LEFT) {
                input->mouse_left_pressed = 0;
                input->mouse_left_down = 0;
                input->mouse_left_up = 1;
            }
        }

        if (event_type == SDL_KEYDOWN) {
            const int code = input->event.key.keysym.scancode;
            input->pressed_keys[code] = 1;
            input->keys_down[code] = 1;
        } else if (event_type == SDL_KEYUP) {
            const int code = input->event.key.keysym.scancode;
            input->pressed_keys[code] = 0;
            input->keys_up[code] = 1;
        }
    }
}
