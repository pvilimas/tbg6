#include "room.hpp"

const std::string Room::DirToString[Direction::Count] = {
    "north",
    "south",
    "east",
    "west"
};

const Room::Direction Room::ReverseDirection[Room::Direction::Count] = {
    Room::Direction::South,
    Room::Direction::North,
    Room::Direction::West,
    Room::Direction::East
};

Room::Room(std::string name, Room::Messages messages) {
    this->name = name;

    for (Room*& p : this->paths) {
        p = nullptr;
    }

    this->messages = messages;
    this->playerVisited = false;
}

Room* Room::GetPath(Room::Direction dir) {
    return this->paths[dir];
}

void Room::Link(Room& other, Room::Direction dir, bool bothways) {
    this->paths[dir] = &other;
    if (bothways) {
        other.paths[Room::ReverseDirection[dir]] = this;
    }
}

std::string Room::GetName() {
    return this->name;
}

std::vector<Command> Room::GetCommands() {
    std::vector<Command> commands;
    return commands;
}

Room::Messages Room::GetMessages() {
    return messages;
}

std::string Room::GetEnterMsg() {
    return (this->playerVisited) ? this->messages.OnEnter : this->messages.OnFirstEnter;
}

void Room::Visit() {
    this->playerVisited = true;
}