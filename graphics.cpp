#include "graphics.hpp"

const std::string graphics::TextArea::prompt = "> ";
const float graphics::TextArea::cursorBlinkInterval = 0.8f;
const float graphics::TextArea::keypressInterval = 0.05f;

graphics::TextArea::TextArea(int x, int y, int width, int height, std::function<void(std::string)> eval)
    : keypressTimer(graphics::TextArea::keypressInterval) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = "\0";
    this->eval = eval;
}

void graphics::TextArea::Draw() {
    DrawRectangle(this->x, this->y, this->width, this->height, BLACK);
    DrawText((prompt + this->text).c_str(), x, y, 20, WHITE);
}

void graphics::TextArea::AddChar(KeyboardKey k) {
    if (KEY_A <= k && k <= KEY_Z) {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            this->text += (char)k;
        } else {
            // uppercase
            this->text += (char)k + 32;
        }
    } else if (k == KEY_SPACE) {
        this->text += (char)k;
    } else if (k == KEY_BACKSPACE && this->text.size() > 0) {
        this->text.pop_back();
        // strip text
        if (this->text.back() == '\n') {
            this->text.pop_back();
        }
    } else if (k == KEY_ENTER) {
        this->eval(this->text);
    } else if (k == KEY_ESCAPE) {
        exit(1);
    }
}

void graphics::TextArea::SetText(std::string text) {
    this->text = text;
}