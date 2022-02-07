#ifndef __GAME_HEADER__
#define __GAME_HEADER__

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

#include "raylib.h"

#include "command.hpp"
#include "room.hpp"
#include "graphics.hpp"

using namespace std;
using namespace graphics;

class Player {
    private:

        Room* currentRoom;

    public:

        Player();

        Room *GetRoom();
        void SetRoom(Room* r);
        void Move(Room::Direction dir);
};

class Game {
    
    public:

        class ExitGameException {};
        class RestartGameException {};

        enum class GameState {
            Title,
            Gameplay
        };

        class Messages {
            public:
            
            static const string
                // displayed on the title screen
                Title,
                // when the player starts the game
                GameStart,
                // response to command "help"
                Help,
                // response to unknown command
                UnknownCommand,
                // when a direction is unclear or missing
                UnknownDirection,
                // when the player can't go that way
                BlockedDirection;
        };

    private:

        string winTitle;
        int winWidth, winHeight;
        Texture2D texture;
        TextBox textbox;
        GameState state;
        Player player;
        vector<Room> rooms;

        vector<Command> GetCommands();
        static vector<KeyboardKey> GetKeysPressed();

    public:
    

        Game(string winTitle, int winWidth, int winHeight);
        
        void Init();
        void Run();
        void Reset();
        void Destroy();

        void Draw();

        void SetState(GameState new_state);
        void EvalText(string text);

        void TryMove(Room::Direction dir);

};

#endif /* __GAME_HEADER__ */