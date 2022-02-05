#ifndef __TEXTAREA_HEADER__
#define __TEXTAREA_HEADER__

#include <iostream>
#include <vector>

#include "raylib.h"

#include "utils.hpp"

namespace graphics {
    using namespace std;
    using namespace utils;

    class TextArea {

        private:
            
            // displayed at the start of lines
            static const string prompt;
            static const float cursorBlinkInterval;
            static const float keypressInterval;
            
            int x, y, width, height;
            string text;
            function<void(string)> eval;

            Timer keypressTimer;
            
        
        public:
        
            TextArea(int x, int y, int width, int height, function<void(string)> eval);
            
            void Draw();
            void AddChar(KeyboardKey k);
            void SetText(string text);
    };
}

#endif /* __TEXTAREA_HEADER__ */