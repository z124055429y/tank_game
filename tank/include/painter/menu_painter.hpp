#if !defined(_MENU_PAINTER_)
#define _MENU_PAINTER_

#include <list>
#include <string>

#include "element/menu.hpp"
#include "base/allocate.hpp"

class MenuPainter
{
private:
    
public:
    void draw(Menu *menu) {
        if (menu == nullptr) return;
        int rows, cols;
        int **bitmap = menu->getBitmap(rows, cols);
        
        fillSpace(bitmap, rows, cols, ' ');
        std::list<std::string> items = menu->getItems();
        int i = 0;
        for (auto item: items)
        {
            for (size_t j = 0; j < item.size(); j++)
            {
                bitmap[i][j] = item[j];
            }
            i++;
        }
    }
};

#endif // _MENU_PAINTER_
