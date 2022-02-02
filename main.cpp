#include "game.hpp"
#include "textarea.hpp"

using namespace std;
using std::vector;

int main() {
    InitWindow(640, 460, "textbasedgame");
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    auto img = LoadImage("assets/a.png");
    auto texture = LoadTextureFromImage(img);
    UnloadImage(img);

    TextArea t = TextArea { 0, 360, 640, 100 };

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(texture, 0, 0, WHITE);
        t.draw();
        auto keys = Game::keys_pressed();
        for (int i = 0; i < keys.size(); i++) {
            t.addchar(keys[i]);
        }
        
        EndDrawing();
    }

    CloseWindow();
}
