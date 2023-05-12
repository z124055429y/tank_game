#if !defined(_MENU_HPP_)
#define _MENU_HPP_

#include <list>
#include <string>

#include "base/element.hpp"

class Menu: public Element
{
private:
    std::list<std::string> mItems;
public:
    Menu(int x, int y, std::list<std::string> items);
    ~Menu();
    std::list<std::string> getItems() { return mItems; }
};



#endif // _MENU_HPP_
