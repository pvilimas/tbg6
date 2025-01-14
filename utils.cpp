#include "utils.hpp"

const std::function<void()> utils::Timer::defaultCallback = []{};

utils::Timer::Timer(float interval, std::function<void()> callback) {
    this->interval = interval;
    this->lastRecorded = 0;
    this->callback = callback;
}

/* returns true if an interval has passed, then resets the interval */
bool utils::Timer::IntervalPassed() {
    float newTime = GetTime();
    if (this->lastRecorded + this->interval <= newTime) {
        this->lastRecorded = newTime;
        return true;
    }
    return false;
}

/* calls the callback if needed */
void utils::Timer::CheckTime() {
    if (this->IntervalPassed()) {
        this->callback();
    }
}

void utils::Timer::Reset() {
    this->lastRecorded = 0;
}

std::string utils::join_strings(std::vector<std::string> v, std::string delim) {
    std::string ret = "";
    int i;
    for (i = 0; i < v.size() - 1; i++) {
        ret += v.at(i);
        ret += delim;
    }
    ret += v.at(i);
    return ret;
}