#ifndef __ROOM_HEADER__
#define __ROOM_HEADER__

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

#include "item.hpp"
#include "command.hpp"

class Room {

    public:

        /* UL - so it can be use as an index */
        enum Direction : unsigned long {
            North,
            South,
            East,
            West,

            Count,
            Invalid
        };

        /* direction attributes */
        static const std::string DirToString[Direction::Count];
        static const Direction ReverseDirection[Direction::Count];

        /* local to each room */
        class Messages {
            public:
            std::string OnEnter;
            std::string OnFirstEnter;
            std::string OnStay;
            std::string OnLook;
        };


    private:

        /* the internal and displayed name of the room */
        std::string name;
        /* adjoining rooms, indexed by direction */
        Room* paths[Direction::Count];
        /* has the player visited yet? use GetEnterMsg() and dw about this directly */
        bool playerVisited;
        /* messages displayed in different contexts */
        Room::Messages messages;
        /* all items currently in the room */
        std::vector<Item&> items;
    
    public:

        Room(std::string name, Room::Messages messages);

        void Link(Room& other, Direction dir, bool bothways = true);
        void AddItem(Item& item);
        
        Room* GetPath(Direction dir);
        std::string GetName();
        Messages GetMessages();
        std::vector<Command> GetCommands();

        /* returns OnEnter or OnFirstEnter (based on if player has visited) */ 
        std::string GetEnterMsg();

        /* sets playerVisited to true */
        void Visit();
};

#endif /* __ROOM_HEADER__ */