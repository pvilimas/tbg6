#include "textarea.hpp"

const string TextArea::prompt = "> ";

TextArea::TextArea(int x, int y, int width, int height, function<void(string)> eval) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = "\0";
    this->eval = eval;
}

void TextArea::Draw() {
    DrawRectangle(this->x, this->y, this->width, this->height, BLACK);
    DrawText((prompt + this->text).c_str(), x, y, 20, WHITE);
}

void TextArea::AddChar(KeyboardKey k) {
    if (KEY_A <= k && k <= KEY_Z) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            this->text += (char)k;
        } else {
            // uppercase
            this->text += (char)k + 32;
        }
    } else if (k == KEY_SPACE) {
        this->text += (char)k;
    } else if (k == KEY_BACKSPACE) {
        this->text.pop_back();
        // strip text
        if (this->text.back() == '\n') {
            this->text.pop_back();
        }
    } else if (k == KEY_ENTER) {
        this->eval(this->text);
    }
}

void TextArea::SetText(string text) {
    this->text = text;
}