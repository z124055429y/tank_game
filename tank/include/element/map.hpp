#if !defined(_MAP_HPP_)
#define _MAP_HPP_

#include "base/element.hpp"
#include "action/touch.hpp"

/**
 * 地图类
 * 
 * ‘#’: 铁墙&边界: 不可破坏: 不可穿越
 * ‘^’: 土墙: 可以破坏: 不可穿越
 * ‘Y’: 草地: 不可破坏: 可以穿越
 * ‘~’: 河流: 不可破坏: 仅子弹可穿越
 * 
*/

#define MASK_LAND       (0xff)
#define FLAG_BORDER     (1)
#define FLAG_IRON_WALL  (1<<1)
#define FLAG_MUD_WALL   (1<<2)
#define FLAG_RIVER      (1<<3)
#define FLAG_GRASS      (1<<4)

/**
 * 地图类
*/
class Map: public Element, public Touch
{
private:
    int **mFlag;
    void initBorder();
public:
    Map(int rows, int cols);
    ~Map();
    int* operator[](const int pos);
    int touch(Element *origin);
};


#endif // _MAP_HPP_
