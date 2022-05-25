#include "command.hpp"

Command::Command(std::string name, std::string pattern, std::function<void()> onMatch) {
    this->name = name;
    // ignore case by default
    this->regex = std::regex(pattern, std::regex_constants::ECMAScript | std::regex_constants::icase);
    this->onMatch = onMatch;
}

/* returns true if it FULLY matched false otherwise */
bool Command::IsMatch(std::string s) const {
    return regex_match(s, this->regex);
}

/* calls the above */
void Command::TryMatch(std::string s) const {
    if (this->IsMatch(s)) {
        this->onMatch();
    }
}