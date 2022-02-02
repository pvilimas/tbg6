#include "game.hpp"

Game::Game(string win_title, int win_width, int win_height) {
    this->win_title = win_title;
    this->win_width = win_width;
    this->win_height = win_height;
}

void Game::init() {
    InitWindow(this->win_width, this->win_height, this->win_title.c_str());
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    auto img = LoadImage("assets/a.png");
    this->texture = LoadTextureFromImage(img);
    UnloadImage(img);
}

void Game::run() {
    auto t = TextArea(0, this->win_height-100, this->win_width, 100);
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(this->texture, 0, 0, WHITE);
        t.draw();
        auto keys = Game::keys_pressed();
        for (int i = 0; i < keys.size(); i++) {
            t.addchar(keys[i]);
        }
        
        EndDrawing();
    }
}

void Game::destroy() {
    UnloadTexture(this->texture);
    CloseWindow();
    delete this;
}

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