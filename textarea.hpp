#ifndef __TEXTAREA_HEADER__
#define __TEXTAREA_HEADER__

#include <iostream>
#include <vector>

#include "raylib.h"

using namespace std;

class TextArea {
    int x, y, width, height;
    string text;
    
    // displayed at the start of lines
    static const string prompt;
    
    public:

    TextArea(int x, int y, int width = 640, int height = 100);
    
    void draw(void);
    void addchar(KeyboardKey k);
};

#endif /* __TEXTAREA_HEADER__ */