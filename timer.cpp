#include "timer.hpp"

Timer::Timer(float interval, function<void()> callback) {
    this->interval = interval;
    this->lastRecorded = 0.0f;
    this->callback = callback;
}

/* returns true if an interval has passed, then resets the interval */
bool Timer::IntervalPassed() {
    float newTime = GetTime();
    if (newTime - this->lastRecorded >= this->interval) {
        this->lastRecorded = newTime;
        return true;
    }
    return false;
}

/* calls the callback if needed */
void Timer::CheckTimer() {
    if (this.TimeIntervalPassed()) {
        this->callback();
    }
}


void Timer::Reset() {
    this->lastRecorded = 0;
}