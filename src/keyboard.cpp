#include "keyboard.h"
#include <SDL2/SDL_keycode.h>
#include <iostream>

#define MAX_KEYBOARD_KEYS 256
static KeyBoardKey keyboardKeys[MAX_KEYBOARD_KEYS];
static KeyBoardKey LastKeyboardKeys[MAX_KEYBOARD_KEYS];

bool IsKeyUp(int key) {
    if (key < 0 || key >= MAX_KEYBOARD_KEYS) return false;
    return !keyboardKeys[key].state;
}

bool IsKeyDown(int key) {
    if (key < 0 || key >= MAX_KEYBOARD_KEYS) return false;
    return keyboardKeys[key].state;
}

bool IsKeyPressed(int key) {
    if (key < 0 || key >= MAX_KEYBOARD_KEYS) return false;
    // Key is pressed if current state is true and previous state was false
    bool pressed = (keyboardKeys[key].state && !LastKeyboardKeys[key].state);
    if (pressed) {
        DEBUGLOG("Key %i pressed\n", key);
    }
    return pressed;
}

void UpdateKeyboardState(SDL_Event event) {
    int key = event.key.keysym.sym;

    if (key < 0 || key >= MAX_KEYBOARD_KEYS) return; // Ignore out-of-range keys

    if (event.type == SDL_KEYDOWN) {
        keyboardKeys[key].key = key;
        keyboardKeys[key].state = true;
        DEBUGLOG("Key %i down\n", key);
    } else if (event.type == SDL_KEYUP) {
        keyboardKeys[key].key = key;
        keyboardKeys[key].state = false;
        DEBUGLOG("Key %i up\n", key);
    }
	UpdatePreviousKeyboardState();
}

void UpdatePreviousKeyboardState() {
    for (int i = 0; i < MAX_KEYBOARD_KEYS; ++i) {
        if (LastKeyboardKeys[i].state != keyboardKeys[i].state) {
            DEBUGLOG("Key %i state changed: %d -> %d\n",
                     i, LastKeyboardKeys[i].state, keyboardKeys[i].state);
        }
        LastKeyboardKeys[i].state = keyboardKeys[i].state;
    }
}
