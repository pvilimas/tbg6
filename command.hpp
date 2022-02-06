#ifndef __COMMAND_HEADER__
#define __COMMAND_HEADER__

#include <regex>

class Command {

    private:
    
        std::string name;
        std::regex regex;

    public:

        std::function<void()> onMatch;

        Command(std::string name, std::string pattern, std::function<void()> onMatch);

        bool IsMatch(std::string s) const;

};

#endif /* __COMMAND_HEADER__ */