#include <iostream>

#include "raylib.h"

using namespace std;

int main() {
    InitWindow(800, 500, "textbasedgame");
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("a", 100, 100, 20, BLACK);
        
        EndDrawing();
    }

    CloseWindow();
}
