#ifndef __GAME_HEADER__
#define __GAME_HEADER__

#include <iostream>
#include <vector>

#include "raylib.h"

using namespace std;

class Game {

    public:
    
    static vector<KeyboardKey> keys_pressed(void);
};

#endif /* __GAME_HEADER__ */