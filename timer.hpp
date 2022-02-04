#ifndef __TIMER_HEADER__
#define __TIMER_HEADER__

#include "raylib.h"

using namespace std;

class Timer {
    private:
        
        float interval;
        float lastRecorded;
        function<void()> callback;

    public:

        Timer(float interval, function<void()> callback);
        bool IntervalPassed();
        void CheckTime();
        void Reset();
}

#endif /* __TIMER_HEADER__ */