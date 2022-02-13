#ifndef __ITEM_HEADER__
#define __ITEM_HEADER__

#include <string>
#include <vector>

#include "command.hpp"

class Item {
    public:

        typedef struct {
            bool canUse;
            bool canCarry;
        } ItemAttrs;

    private:

        std::string name;
        std::string _repr;
        Item::ItemAttrs attrs;
    
    public:

        Item(std::string name, Item::ItemAttrs attrs);
        
        std::vector<std::string> GetCommands();
        
        std::string repr();


};

#endif /* __ITEM_HEADER__ */
