#include <iostream>

#include "raylib.h"

using namespace std;

// displayed at the start of lines
const string prompt = "> ";

class TextArea {
    int x, y, width, height;
    string text;
    
    public:

        TextArea(int xpos, int ypos, int w=100, int h=100) {
            x = xpos;
            y = ypos;
            width = w;
            height = h;
            text = "text will go here\n> more stuff here\n> go north";
        }

        void draw(void) {
            DrawRectangle(x, y, width, height, BLACK);
            DrawText((prompt + text).c_str(), x, y, 20, WHITE);
        }
};

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
        
        EndDrawing();
    }

    CloseWindow();
}
