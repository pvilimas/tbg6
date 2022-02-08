#include "game.hpp"
#include "graphics.hpp"

using namespace std;
using std::vector;

/*
    TODO:

    - switch from headers to modules

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
    - quit confirmation

    ...

    - read a fucking style guide (esp. constructors - change the names)
        - get rid of all the "this"
    - capslock/numpad/hold backspace to delete text
        - keyboard shortcuts to delete a word or a whole line
    - make timers exact (issue w/ frametime?)
    - start designing the game itself - a demo can only go so far without an idea
    - NPCs (definitely fucking do this one at some point)
        - sell/trade items
        - talk to them
        - dialog tree like before
    - typing suggestions (autofill with tab maybe)
    - a (useful) help cmd
    - SMW style pixel fadeout for the pics?

    things to not do (for a while at least):
    
    - clickable NSEW buttons

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
