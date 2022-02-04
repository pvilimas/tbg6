#include "game.hpp"
#include "textarea.hpp"

using namespace std;
using std::vector;

/*
    TODO:
    
    - add timers (for first thing below)
    - TextArea:
        - make holding keys work properly (IsKeyPressed/Down) - not too often but often enough
        - add support for more characters (!@#$%^&*(), 0-9, ~`_+-={}[]|\:";'<>?,./`")
        - have a caps variable to detect caps lock (or just check with the OS if it's on)
        - \t for tab
    - Command:
        - make the class
        - Command::Command(name, pattern, onCall) - like before
        - game failsafe commands that match everything
    - game commands:
        - q(uit)?, exit, help
    - Room:
        - NSEW to start off
        - some sort of data structure, probably a Directions class which holds dir attrs for each
            linked to a room
        - Command to match each direction
    - Game:
        - invent a starting room and an adjacent room
        - set up a Player class and game.player
            - currentRoom
        - game loop, poll for input, check commands in order
            - Make the commands strictly ordered - ranges:
                gamecommands = [npc cmds] + [room cmds] + [item cmds] + FAILSAFE1 + FS2 + [other failsafes] + MATCH_ALL
    - Item:
        - make this whole class
    - Room:
        - vector<Item> items
    - Player
        - vector<Item> inventory
        - takeItem, dropItem, hasItem
            - correct error messages "you are/you're not holding that!"
    - Game
        - error messages - lots of them

    ...

    - start designing the game itself - a demo can only go so far without an idea
    - NPCs (definitely fucking do this one at some point)
        - sell/trade items
        - talk to them
        - dialog tree like before
    - 

*/

int main() {

    auto game = new Game("textbasedgame", 640, 460);

    game->Init();
    while (true) {
        try {
            game->Run();
        } catch (Game::ExitGameException e) {
            break;
        } catch (Game::RestartGameException e) {
            game->Reset();
            continue;
        }
    }
    
    game->Destroy();
}
