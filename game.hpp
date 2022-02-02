#ifndef __GAME_HEADER__
#define __GAME_HEADER__

#include <iostream>
#include <vector>

#include "raylib.h"

#include "textarea.hpp"

using namespace std;

class Game {
    string win_title;
    int win_width, win_height;
    Texture2D texture;

    public:
    Game(string win_title, int win_width, int win_height);
    
    void init();
    void run();
    void destroy();

    static vector<KeyboardKey> keys_pressed();
    
};

#endif /* __GAME_HEADER__ */