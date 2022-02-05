#ifndef __UTILS_HEADER__
#define __UTILS_HEADER__

#include "raylib.h"

namespace utils {
    class Timer {
        private:
            
            float interval;
            float lastRecorded;
            std::function<void()> callback;

        public:

            Timer(float interval, std::function<void()> callback);
            bool IntervalPassed();
            void CheckTime();
            void Reset();
    }
}

#endif /* __UTILS_HEADER__ */