#include "graphics.hpp"

const std::string graphics::TextBox::prompt = "> ";

graphics::TextBox::TextBox(int x, int y, int width, int height, std::function<void(std::string)> eval)
    : keypressTimer(graphics::TextBox::keypressInterval) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->playerIn = "\0";
    this->eval = eval;
    this->cursorPos = 0;
}

void graphics::TextBox::Draw() {

    // for adding chars
    static int currLine = 0;

    DrawRectangle(this->x, this->y, this->width, this->height, BLACK);

    DrawText((prompt + this->playerIn).c_str(), x + 3, y+height-25, 20, WHITE);
    
    DrawText(this->gameOut[0].c_str(), x + 5, y, 20, Color {200, 200, 200, 255});
    DrawText(this->gameOut[1].c_str(), x + 5, y+((height-25))/4, 20, Color {200, 200, 200, 255});
    DrawText(this->gameOut[2].c_str(), x + 5, y+(2*(height-25))/4, 20, Color {200, 200, 200, 255});
    DrawText(this->gameOut[3].c_str(), x + 5, y+(3*(height-25))/4, 20, Color {200, 200, 200, 255});

    // pop from char queue

    if (!this->charDispQueue.empty()) {
        char c = this->charDispQueue.front();
        if (c == '\n') {
            currLine++;
        } else {
            this->gameOut[currLine] += c;
        }
        this->charDispQueue.pop();
    } else {
        currLine = 0;
    }

    // cursor blink

    if ((int)(GetTime() * 10000) % 15000 >= 7500) {
        float cursorX = x + 5 + MeasureText((this->prompt + this->playerIn.substr(0, this->cursorPos)).c_str(), 20);
        float cursorY = y + height - 15;
        float cursorW = 1.4;
        float cursorH = 20;

        DrawLineEx({ cursorX, cursorY - cursorH / 2 }, { cursorX, cursorY + cursorH / 2 }, cursorW, WHITE);
    }

}

void graphics::TextBox::AddChar(KeyboardKey k, bool shift) {

    if (!this->charDispQueue.empty()) {
        return;
    }

    /* backspace */
    if (k == KEY_BACKSPACE && this->playerIn.size() > 0 && this->cursorPos > 0) {
        //this->text.pop_back();
        this->playerIn.erase(this->playerIn.begin() + this->cursorPos-1);
        this->cursorPos--;
        return;
    }
    /* enter */
    else if (k == KEY_ENTER) {
        this->eval(this->playerIn);
        this->playerIn.clear();
        this->cursorPos = 0;
    }
    /* escape */
    else if (k == KEY_ESCAPE) {
        exit(0);
    }
    /* ignore these, already accounted for */
    else if (k == KEY_LEFT_SHIFT || k == KEY_RIGHT_SHIFT) {}
    /* arrow keys to control cursor pos */
    else if (k == KEY_UP) {
        this->cursorPos = 0;
    } else if (k == KEY_DOWN) {
        this->cursorPos = this->playerIn.length() - 1;
    } else if (k == KEY_LEFT) {
        this->cursorPos = max((int) this->cursorPos-1, (int) 0);
    } else if (k == KEY_RIGHT) {
        this->cursorPos = min((int) this->cursorPos+1, (int) this->playerIn.length());
    }
    /* everything else */
    else {
        // use .at() here (not operator[]) to avoid error
        try {
            this->playerIn.insert(this->playerIn.begin() + this->cursorPos, (shift) ? utils::keyChars.at(k).shift : utils::keyChars.at(k).normal);
            this->cursorPos++;
        } catch (out_of_range) {}
    }
}

void graphics::TextBox::SetPlayerText(std::string text) {
    this->playerIn = text;
    this->cursorPos = text.size();
}

void graphics::TextBox::SetGameText(std::string text) {
    
    for (std::string& str : this->gameOut) {
        str.clear();
    }
    // clear the queue
    this->charDispQueue = std::queue<char>();

    auto lines = this->SplitText(text);

    //for (int i = graphics::TextBox::lineCount-1; i >= 0; i--) {
    for (int i = 0; i < graphics::TextBox::lineCount; i++) {
        auto line = lines.front();
        for (char c : line) {
            if (c == '\n') {
                i++;
                if (i >= graphics::TextBox::lineCount) {
                    // will break from both loops
                    break;
                }
            } else {
                this->charDispQueue.push(c);
            }
        }
        this->charDispQueue.push('\n');
        lines.pop();
    }
}

std::queue<std::string> graphics::TextBox::SplitText(std::string text) {

    std::queue<std::string> res;
    std::regex line_regex = std::regex("(.{1,58})(?:(\\s)+|$)");

    for (std::sregex_iterator i = std::sregex_iterator(text.begin(), text.end(), line_regex); i != std::sregex_iterator(); i++) {
        res.push((*i).str());
    }

    // pad it with empty lines
    while (res.size() < graphics::TextBox::lineCount) {
        res.push("");
    }

    return res;

}