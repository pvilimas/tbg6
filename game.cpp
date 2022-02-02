#include "game.hpp"

vector<KeyboardKey> Game::keys_pressed(void) {
    vector<KeyboardKey> keys;
    for (int k = KEY_A; k < KEY_Z; k++) {
        if (IsKeyPressed(k)) {
            keys.push_back((KeyboardKey)k);
        }
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        keys.push_back(KEY_BACKSPACE);
    } else if (IsKeyPressed(KEY_SPACE)) {
        keys.push_back(KEY_SPACE);
    }
    return keys;
}