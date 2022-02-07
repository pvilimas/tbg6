#include "room.hpp"

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
        other.paths[dir] = this;
    }
}