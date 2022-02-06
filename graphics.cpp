#include "graphics.hpp"

const std::string graphics::TextArea::prompt = "> ";
const float graphics::TextArea::cursorBlinkInterval = 0.8;
const float graphics::TextArea::keypressInterval = 0.1f;

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
    
    // cursor blink

    if ((int)(GetTime() * 10000) % 15000 >= 7500) {
        float cursorX = x + 4 + MeasureText((prompt + this->text).c_str(), 20);
        float cursorY = y + 10;
        float cursorW = 2;
        float cursorH = 20;

        DrawLineEx({ cursorX, cursorY - cursorH / 2 }, { cursorX, cursorY + cursorH / 2 }, cursorW, WHITE);
    }

}

void graphics::TextArea::AddChar(KeyboardKey k, bool shift) {
    // !@#$%^&*(), 0-9, ~`_+-={}[]|\:";'<>?,./`"
    if (this->keypressTimer.IntervalPassed()) {
        /* backspace */
        if (k == KEY_BACKSPACE && this->text.size() > 0) {
            this->text.pop_back();
            return;
        }
        /* enter */
        else if (k == KEY_ENTER) {
            this->eval(this->text);
        }
        /* escape */
        else if (k == KEY_ESCAPE) {
            exit(0);
        }
        /* ignore these, already accounted for */
        else if (k == KEY_LEFT_SHIFT || k == KEY_RIGHT_SHIFT) {}
        /* everything else */
        else {
            // use .at() here (not operator[]) to avoid error
            try {
                this->text += ((shift) ? utils::keyChars.at(k).shift : utils::keyChars.at(k).normal);
            } catch (out_of_range e) {}
        }
    }
}

void graphics::TextArea::SetText(std::string text) {
    this->text = text;
}