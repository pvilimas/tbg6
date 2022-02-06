#ifndef __TEXTAREA_HEADER__
#define __TEXTAREA_HEADER__

#include <iostream>
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
            static const float cursorBlinkInterval;
            static const float keypressInterval;
            
            int x, y, width, height;
            string text;
            int cursorPos;
            function<void(string)> eval;

            Timer keypressTimer;
            
        
        public:
        
            TextBox(int x, int y, int width, int height, function<void(string)> eval);
            
            void Draw();
            void AddChar(KeyboardKey k, bool shift);
            void SetText(string text);
    };
}

#endif /* __TEXTAREA_HEADER__ */