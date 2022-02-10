#include "item.hpp"

Item::Item(std::string name, Item::ItemAttrs attrs) {
    _name = name;
    _attrs = attrs;
}

std::string Item::repr() {
    return _repr;
}

std::vector<std::string> Item::GetCommands() {

}