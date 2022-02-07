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

Room::Room(std::string name) {
    this->name = name;

    for (Room*& p : this->paths) {
        p = nullptr;
    }
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