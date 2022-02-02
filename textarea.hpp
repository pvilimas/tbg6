#ifndef __TEXTAREA_HEADER__
#define __TEXTAREA_HEADER__

#include <iostream>
#include <vector>

#include "raylib.h"

using namespace std;

class TextArea {
    int x, y, width, height;
    string text;
    
    public:

        // displayed at the start of lines
        static const string prompt;

        TextArea(int xpos, int ypos, int w, int h);
        
        void draw(void);
        void addchar(KeyboardKey k);
};

#endif /* __TEXTAREA_HEADER__ */