#include "graphics.hpp"

const std::string graphics::TextBox::prompt = "> ";
const float graphics::TextBox::cursorBlinkInterval = 0.8;
const float graphics::TextBox::keypressInterval = 0.1f;

graphics::TextBox::TextBox(int x, int y, int width, int height, std::function<void(std::string)> eval)
    : keypressTimer(graphics::TextBox::keypressInterval) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = "\0";
    this->eval = eval;
    this->cursorPos = 0;
}

void graphics::TextBox::Draw() {

    DrawRectangle(this->x, this->y, this->width, this->height, BLACK);
    DrawText((prompt + this->text).c_str(), x, y, 20, WHITE);
    
    // cursor blink

    if ((int)(GetTime() * 10000) % 15000 >= 7500) {
        float cursorX = x + 2 + MeasureText((this->prompt + this->text.substr(0, this->cursorPos)).c_str(), 20);
        float cursorY = y + 10;
        float cursorW = 1.4;
        float cursorH = 20;

        DrawLineEx({ cursorX, cursorY - cursorH / 2 }, { cursorX, cursorY + cursorH / 2 }, cursorW, WHITE);
    }

}

void graphics::TextBox::AddChar(KeyboardKey k, bool shift) {
    /* backspace */
    if (k == KEY_BACKSPACE && this->text.size() > 0 && this->cursorPos > 0) {
        //this->text.pop_back();
        this->text.erase(this->text.begin() + this->cursorPos-1);
        this->cursorPos--;
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
    /* arrow keys to control text */
    else if (k == KEY_UP) {
        this->cursorPos = 0;
    } else if (k == KEY_DOWN) {
        this->cursorPos = this->text.length() - 1;
    } else if (k == KEY_LEFT) {
        this->cursorPos = max((int) this->cursorPos-1, (int) 0);
    } else if (k == KEY_RIGHT) {
        this->cursorPos = min((int) this->cursorPos+1, (int) this->text.length());
    }
    /* everything else */
    else {
        // use .at() here (not operator[]) to avoid error
        try {
            this->text.insert(this->text.begin() + this->cursorPos, (shift) ? utils::keyChars.at(k).shift : utils::keyChars.at(k).normal);
            this->cursorPos++;
        } catch (out_of_range) {}
    }
}

void graphics::TextBox::SetText(std::string text) {
    this->text = text;
}