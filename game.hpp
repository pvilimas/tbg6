#ifndef __GAME_HEADER__
#define __GAME_HEADER__

#include <algorithm>
#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "raylib.h"

#include "item.hpp"
#include "command.hpp"
#include "room.hpp"
#include "graphics.hpp"

using namespace std;
using namespace graphics;

class Player {
    private:

        Room* currentRoom;
        vector<Item> inventory;

    public:

        Player();

        Room *GetCurrentRoom();
        void SetCurrentRoom(Room* r);
        void Move(Room::Direction dir);

        vector<Item> GetInv();

        bool TryTakeItem(Item item);
        bool TryDropItem(Item item);
        
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

        /* STATIC METHODS */

        static vector<KeyboardKey> GetKeysPressed();

        /* INSTANCE VARS */

        /* the window title */
        string winTitle;
        /* starting dimensions of the window */
        int winWidth, winHeight;
        /* currently the only texture used - add more later */
        Texture2D texture;
        /* the only textbox that will ever be needed */
        TextBox textbox;
        /* which state the game is currently in */
        GameState state;
        /* the only player */
        Player player;
        /* a collection of all possible rooms */
        unordered_map<string, Room&> rooms;
        /* a collection of all possible items */
        unordered_map<string, Item&> items;

        /* INSTANCE METHODS */

        vector<Command> GetCommands();

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
        
        string GetPlayerInvAsString();

};

#endif /* __GAME_HEADER__ */