#include "textarea.hpp"

const string TextArea::prompt = "> ";

TextArea::TextArea(int xpos, int ypos, int w=100, int h=100) {
    x = xpos;
    y = ypos;
    width = w;
    height = h;
    text = "text will go here\n> more stuff here\n> go north";
}

void TextArea::draw(void) {
    DrawRectangle(x, y, width, height, BLACK);
    DrawText((prompt + text).c_str(), x, y, 20, WHITE);
}

void TextArea::addchar(KeyboardKey k) {
    if (k == KEY_SPACE || KEY_A <= k && k <= KEY_Z) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            text += (char)k;
        } else {
            text += (char)k + 32;
        }
    } else if (k == KEY_BACKSPACE) {
        text.pop_back();
        // strip text
        if (text.back() == '\n') {
            text.pop_back();
        }
    }
}