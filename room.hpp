#ifndef __ROOM_HEADER__
#define __ROOM_HEADER__

#include <algorithm>
#include <cctype>
#include <string>

class Room {

    public:

        enum Direction : unsigned long {

            North = 0,
            South,
            East,
            West,

            Count,
            Invalid = 5
        };

        static const std::string DirToString[Direction::Count];
        static const Direction ReverseDirection[Direction::Count];

    private:

        std::string name;
        Room* paths[Direction::Count];
    
    public:

        Room(std::string name);
        void Link(Room& other, Room::Direction dir, bool bothways = true);
        Room* GetPath(Room::Direction dir);
        std::string GetName();
};

#endif /* __ROOM_HEADER__ */