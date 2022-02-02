#include <iostream>
#include <vector>

#include "textarea.hpp"

#include "raylib.h"

using namespace std;
using std::vector;

vector<KeyboardKey> keys_pressed(void) {
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

int main() {
    InitWindow(640, 460, "textbasedgame");
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    auto img = LoadImage("assets/a.png");
    auto texture = LoadTextureFromImage(img);
    UnloadImage(img);

    TextArea t = TextArea { 0, 360, 640, 100 };

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(texture, 0, 0, WHITE);
        t.draw();
        auto keys = keys_pressed();
        for (int i = 0; i < keys.size(); i++) {
            t.addchar(keys[i]);
        }
        
        EndDrawing();
    }

    CloseWindow();
}
