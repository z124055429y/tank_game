#include <algorithm>

#include "element/menu.hpp"

Menu::Menu(int x, int y, std::list<std::string> items):mItems(items)
{
    mPos = {x, y};
    int rows = items.size();
    int cols = 0;
    for (auto &&item : items)
    {
        int size = item.size();
        cols = std::max(size, cols);
    }
    mSize = {rows, cols};
    pBitmap = allocSpace(rows, cols);
}

Menu::~Menu()
{
    // pBitmap已经交给父进程释放, 不用担心
}