#include "game.hpp"

Game::Game(string win_title, int win_width, int win_height) : textarea(0, win_height-100, win_width, 100, [&] { this->SetState(STATE_GAMEPLAY); }) {
    this->win_title = win_title;
    this->win_width = win_width;
    this->win_height = win_height;
    this->state = STATE_TITLE;
    this->textarea.SetText("You are now on\nthe title screen.");
}

void Game::Init() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(this->win_width, this->win_height, this->win_title.c_str());
    SetTargetFPS(60);

    auto img = LoadImage("assets/a.png");
    this->texture = LoadTextureFromImage(img);
    UnloadImage(img);
}

void Game::Run() {
    while (!WindowShouldClose()) {
        this->Draw();
    }
}

void Game::Destroy() {
    UnloadTexture(this->texture);
    CloseWindow();
    delete this;
}

void Game::Draw() {
    BeginDrawing();

    switch (this->state) {
    
        case STATE_TITLE:
        case STATE_GAMEPLAY: {
            DrawTexture(this->texture, 0, 0, WHITE);
            this->textarea.Draw();
            auto keys = Game::GetKeysPressed();
            for (KeyboardKey& k : keys) {
                this->textarea.AddChar(k);
            }

            break;
        }
        
        default: break;
    }
    
    EndDrawing();
}

/* 
    Contains initialization logic for each state
*/
void Game::SetState(GameState new_state) {

    auto old_state = this->state;

    // if starting the game
    if (old_state == STATE_TITLE && new_state == STATE_GAMEPLAY) {
        this->textarea.SetText("You are now on\nthe gameplay screen.");
    }

    this->state = new_state;
}

vector<KeyboardKey> Game::GetKeysPressed(void) {
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
    } else if (IsKeyPressed(KEY_ENTER)) {
        keys.push_back(KEY_ENTER);
    }
    return keys;
}