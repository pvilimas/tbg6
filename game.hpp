#ifndef __GAME_HEADER__
#define __GAME_HEADER__

#include <iostream>
#include <vector>

#include "raylib.h"

#include "textarea.hpp"

using namespace std;

class Game {

    public:

    class ExitGameException {};
    class RestartGameException {};

    typedef enum {
        STATE_TITLE,
        STATE_GAMEPLAY
    } GameState;

    private:

    string win_title;
    int win_width, win_height;
    Texture2D texture;
    TextArea textarea;

    GameState state;

    public:
    
    Game(string win_title, int win_width, int win_height);
    
    void Init();
    void Run();
    void Reset();
    void Destroy();

    void Draw();

    void SetState(GameState new_state);
    void EvalText(string text);

    static vector<KeyboardKey> GetKeysPressed();
    
};

#endif /* __GAME_HEADER__ */