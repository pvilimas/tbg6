#ifndef __UTILS_HEADER__
#define __UTILS_HEADER__

#include <iostream>

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

}

#endif /* __UTILS_HEADER__ */