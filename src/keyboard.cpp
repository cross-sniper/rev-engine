#include "keyboard.h"
#define MAX_KEYBOARD_KEYS 256
static KeyBoardKey keyboardKeys[MAX_KEYBOARD_KEYS];


bool IsKeyDown(int key) {
    if (key < 0 || key >= MAX_KEYBOARD_KEYS) return false;
    return keyboardKeys[key].state;
}


void UpdateKeyboardState(SDL_Event event) {
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        int key = event.key.keysym.sym;
        bool state = (event.type == SDL_KEYDOWN);

        if (key >= 0 && key < MAX_KEYBOARD_KEYS) {
            keyboardKeys[key].key = key;
            keyboardKeys[key].state = state;
        }
    }
}
