#ifndef __UTILS_HEADER__
#define __UTILS_HEADER__

#include <iostream>
#include <map>

#include "raylib.h"

namespace utils {
    using namespace std;

    class Timer {
        private:
            
            float interval;
            float lastRecorded;
            std::function<void()> callback;

        public:

            static const function<void()> defaultCallback;

            Timer(float interval, function<void()> callback = utils::Timer::defaultCallback);
            bool IntervalPassed();
            void CheckTime();
            void Reset();
    };

    typedef struct { char normal, shift; } CharOpt;

    static const map<KeyboardKey, CharOpt> keyChars = {
        { KEY_SPACE, { ' ', ' ' } },
        { KEY_APOSTROPHE, { '\'', '"' } },
        { KEY_COMMA, { ',', '<' } },
        { KEY_MINUS, { '-', '_' } },
        { KEY_PERIOD, { '.', '>' } },
        { KEY_SLASH, { '/', '?' } },
        { KEY_ZERO, { '0', ')' } },
        { KEY_ONE, { '1', '!' } },
        { KEY_TWO, { '2', '@' } },
        { KEY_THREE, { '3', '#' } },
        { KEY_FOUR, { '4', '$' } },
        { KEY_FIVE, { '5', '%' } },
        { KEY_SIX, { '6', '^' } },
        { KEY_SEVEN, { '7', '&' } },
        { KEY_EIGHT, { '8', '*' } },
        { KEY_NINE, { '9', '(' } },
        { KEY_SEMICOLON, { ';', ':' } },
        { KEY_EQUAL, { '=', '+' } },
        { KEY_A, { 'a', 'A' } },
        { KEY_B, { 'b', 'B' } },
        { KEY_C, { 'c', 'C' } },
        { KEY_D, { 'd', 'D' } },
        { KEY_E, { 'e', 'E' } },
        { KEY_F, { 'f', 'F' } },
        { KEY_G, { 'g', 'G' } },
        { KEY_H, { 'h', 'H' } },
        { KEY_I, { 'i', 'I' } },
        { KEY_J, { 'j', 'J' } },
        { KEY_K, { 'k', 'K' } },
        { KEY_L, { 'l', 'L' } },
        { KEY_M, { 'm', 'M' } },
        { KEY_N, { 'n', 'N' } },
        { KEY_O, { 'o', 'O' } },
        { KEY_P, { 'p', 'P' } },
        { KEY_Q, { 'q', 'Q' } },
        { KEY_R, { 'r', 'R' } },
        { KEY_S, { 's', 'S' } },
        { KEY_T, { 't', 'T' } },
        { KEY_U, { 'u', 'U' } },
        { KEY_V, { 'v', 'V' } },
        { KEY_W, { 'w', 'W' } },
        { KEY_X, { 'x', 'X' } },
        { KEY_Y, { 'y', 'Y' } },
        { KEY_Z, { 'z', 'Z' } },
        { KEY_LEFT_BRACKET, { '[', '{' } },
        { KEY_BACKSLASH, { '\\', '|' } },
        { KEY_RIGHT_BRACKET, { ']', '}' } },
        { KEY_GRAVE, { '`', '~' } },
    };

}

#endif /* __UTILS_HEADER__ */