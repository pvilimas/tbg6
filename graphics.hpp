#ifndef __TEXTAREA_HEADER__
#define __TEXTAREA_HEADER__

#include <chrono>
#include <iostream>
#include <queue>
#include <regex>
#include <string>
#include <thread>
#include <vector>

#include "raylib.h"

#include "utils.hpp"

namespace graphics {
    using namespace std;
    using namespace utils;

    class TextBox {

        private:

            // displayed at the start of lines
            static const string prompt;
            static constexpr float cursorBlinkInterval = 0.8;
            static constexpr float keypressInterval = 0.1;
            static constexpr float charDispInterval = 0.02;
            // how many lines the game text can hold
            static constexpr int lineCount = 4;
            static constexpr int lineLength = 58;
            
            int x, y, width, height;
            int cursorPos;
            string playerIn;
            string gameOut[lineCount];
            function<void(string)> eval;
            // when space is pressed, autotype the rest of the message
            bool purgeQueue;
            queue<char> charDispQueue;

            Timer keypressTimer;
        
        public:
        
            TextBox(int x, int y, int width, int height, function<void(string)> eval);
            
            void Draw();
            void AddChar(KeyboardKey k, bool shift);

            void SetPlayerText(string text);
            void SetGameText(string text);

            queue<string> SplitText(string text);
    };
}

#endif /* __TEXTAREA_HEADER__ */