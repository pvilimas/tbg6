#include "game.hpp"
#include "textarea.hpp"

using namespace std;
using std::vector;

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
