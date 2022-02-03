#ifndef __TEXTAREA_HEADER__
#define __TEXTAREA_HEADER__

#include <iostream>
#include <vector>

#include "raylib.h"

using namespace std;

class TextArea {
    
    int x, y, width, height;
    string text;
    function <void(string)> eval;
    
    // displayed at the start of lines
    static const string prompt;
    
    public:
    
    TextArea(int x, int y, int width, int height, function<void(string)> eval_text);
    
    void Draw();
    void AddChar(KeyboardKey k);
    void SetText(string text);
};

#endif /* __TEXTAREA_HEADER__ */