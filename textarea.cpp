#include "textarea.hpp"

const string TextArea::prompt = "> ";

TextArea::TextArea(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = "text will go here\n> more stuff here\n> go north";
}

void TextArea::draw(void) {
    DrawRectangle(this->x, this->y, this->width, this->height, BLACK);
    DrawText((prompt + this->text).c_str(), x, y, 20, WHITE);
}

void TextArea::addchar(KeyboardKey k) {
    if (KEY_A <= k && k <= KEY_Z) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            this->text += (char)k;
        } else {
            this->text += (char)k + 32;
        }
    } else if (k == KEY_SPACE) {
        this->text += (char)k;
    } else if (k == KEY_BACKSPACE) {
        this->text.pop_back();
        // strip this->text
        if (this->text.back() == '\n') {
            this->text.pop_back();
        }
    }
}