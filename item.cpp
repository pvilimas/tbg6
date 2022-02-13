#include "item.hpp"

Item::Item(std::string name, Item::ItemAttrs attrs) {
    this->name = name;
    this->attrs = attrs;
}

/* string representation */
std::string Item::repr() {
    return this->_repr;
}

/* get specific stuff, like "turn on light */
std::vector<std::string> Item::GetCommands() {

}