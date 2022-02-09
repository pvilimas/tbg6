#ifndef __ROOM_HEADER__
#define __ROOM_HEADER__

#include <algorithm>
#include <cctype>
#include <string>

#include "item.hpp"
#include "command.hpp"

class Room {

    public:

        enum Direction : unsigned long {
            North,
            South,
            East,
            West,

            Count,
            Invalid
        };

        static const std::string DirToString[Direction::Count];
        static const Direction ReverseDirection[Direction::Count];

        class Messages {
            public:
            std::string OnEnter;
            std::string OnFirstEnter;
            std::string OnStay;
            std::string OnLook;
        };


    private:

        std::string name;
        Room* paths[Direction::Count];
        bool playerVisited;
        Room::Messages messages;
    
    public:

        Room(std::string name, Room::Messages messages);
        void Link(Room& other, Direction dir, bool bothways = true);
        Room* GetPath(Direction dir);
        std::string GetName();

        std::vector<Command> GetCommands();
        Messages GetMessages();
        std::string GetEnterMsg();
        void Visit();
};

#endif /* __ROOM_HEADER__ */