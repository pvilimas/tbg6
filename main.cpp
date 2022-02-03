#include "game.hpp"
#include "textarea.hpp"

using namespace std;
using std::vector;

int main() {

    auto game = new Game("textbasedgame", 640, 460);

    game->Init();
    game->Run();
    game->Destroy();
}
