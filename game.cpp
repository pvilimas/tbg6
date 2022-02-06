#include "game.hpp"

Game::Game(string win_title, int win_width, int win_height)
    : textbox(0, win_height-100, win_width, 100, [&](string s) { this->EvalText(s); }) {
    this->win_title = win_title;
    this->win_width = win_width;
    this->win_height = win_height;
    this->state = GameState::Title;
    this->textbox.SetText("title screen");
}

void Game::Init() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(this->win_width, this->win_height, this->win_title.c_str());
    SetExitKey(KEY_ESCAPE);
    SetTargetFPS(60);

    Image img = LoadImage("assets/a.png");
    this->texture = LoadTextureFromImage(img);
    UnloadImage(img);
}

void Game::Run() {
    while (!WindowShouldClose()) {
        this->Draw();
    }
}

void Game::Reset() {}

void Game::Destroy() {
    UnloadTexture(this->texture);
    CloseWindow();
    delete this;
}

void Game::Draw() {
    BeginDrawing();

    switch (this->state) {

        case GameState::Title:
        case GameState::Gameplay: {

            DrawTexture(this->texture, 0, 0, WHITE);
            this->textbox.Draw();

            // handle input
            vector<KeyboardKey> keys = Game::GetKeysPressed();
            // keep this this way
            bool shift = (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT));
            for (KeyboardKey& k : keys) {
                this->textbox.AddChar(k, shift);
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

    GameState old_state = this->state;

    // if starting the game
    if (old_state == GameState::Title && new_state == GameState::Gameplay) {
        this->textbox.SetText("gameplay screen");
    }

    this->state = new_state;
}

void Game::EvalText(string text) {
    for (const Command& c : this->GetCommands()) {
        if (c.IsMatch(text)) {
            c.onMatch();
            break;
        }
    }
}

vector<KeyboardKey> Game::GetKeysPressed(void) {

    // stupid
    // shift not included
    static const int relevantKeys[] = {
        KEY_APOSTROPHE, KEY_COMMA, KEY_MINUS, KEY_PERIOD, KEY_SLASH, KEY_ZERO, KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR,
        KEY_FIVE, KEY_SIX, KEY_SEVEN, KEY_EIGHT, KEY_NINE, KEY_SEMICOLON, KEY_EQUAL, KEY_A, KEY_B, KEY_C, KEY_D,
        KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S,
        KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_LEFT_BRACKET, KEY_BACKSLASH, KEY_RIGHT_BRACKET, KEY_GRAVE,
        KEY_SPACE, KEY_ENTER, KEY_TAB, KEY_BACKSPACE, KEY_DELETE, KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP,
    };

    vector<KeyboardKey> keys;
    KeyboardKey k;

    for (int i = 0; i < (int)(sizeof(relevantKeys) / sizeof(int)); i++) {
        k = (KeyboardKey) relevantKeys[i];
        if (IsKeyPressed(k)) {
            keys.push_back(k);
        }
    }
    return keys;
}

vector<Command> Game::GetCommands() {
    vector<Command> commands;
    
    commands.push_back(Command("Start Game", "start( game)?", [&]{ this->SetState(GameState::Gameplay); }));
    commands.push_back(Command("Quit Game", "(quit)|(exit)( game)?", []{ throw ExitGameException(); }));

    /* everything else will go here */

    commands.push_back(Command("Failsafe: Unknown Command", ".*", []{}));
    return commands;

}