#ifndef __TEXTAREA_HEADER__
#define __TEXTAREA_HEADER__

#include <iostream>
#include <vector>

#include "raylib.h"

namespace graphics {
    class TextArea {

        private:

            int x, y, width, height;
            std::string text;
            std::function<void(std::string)> eval;
            
            // displayed at the start of lines
            static const std::string prompt;
        
        public:
        
            TextArea(int x, int y, int width, int height, std::function<void(std::string)> eval);
            
            void Draw();
            void AddChar(KeyboardKey k);
            void SetText(std::string text);
    };
}

#endif /* __TEXTAREA_HEADER__ */