#ifndef __GAME_HEADER__
#define __GAME_HEADER__

#include <iostream>
#include <vector>

#include "raylib.h"

#include "graphics.hpp"

using namespace std;
using namespace graphics;

class Game {

    public:

        class ExitGameException {};
        class RestartGameException {};

        enum class GameState {
            Title,
            Gameplay
        };

    private:

        string win_title;
        int win_width, win_height;
        Texture2D texture;
        TextArea textarea;

        GameState state;

    public:
    
        static vector<KeyboardKey> GetKeysPressed();

        Game(string win_title, int win_width, int win_height);
        
        void Init();
        void Run();
        void Reset();
        void Destroy();

        void Draw();

        void SetState(GameState new_state);
        void EvalText(string text);
    
};

#endif /* __GAME_HEADER__ */