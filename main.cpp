#include "game.hpp"
#include "graphics.hpp"

using namespace std;
using std::vector;

/*
    TODO:

    - Command:
        - game failsafe commands that match everything
    - game commands:
        - q(uit)?, exit, help
    - Game
        - EvalText command should search the list of commands
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
        - collection of error messages - lots of them

    ...

    - capslock/numpad/hold to delete text
    - make timers exact (frametime?)
    - start designing the game itself - a demo can only go so far without an idea
    - NPCs (definitely fucking do this one at some point)
        - sell/trade items
        - talk to them
        - dialog tree like before
    - typing suggestions (autofill with tab maybe)
    - a (useful) help cmd 

*/

int main() {

    SetTraceLogLevel(LOG_WARNING);

    Game *game = new Game("textbasedgame", 640, 460);

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
