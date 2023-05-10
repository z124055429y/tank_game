#if !defined(_MAP_HPP_)
#define _MAP_HPP_

#include "base/element.hpp"
#include "action/touch.hpp"

#define MASK_LAND       (0xff)
#define LAND_BORDER     (1)
#define LAND_IRON_WALL  (1<<1)
#define LAND_MUD_WALL   (1<<2)
#define LAND_RIVER      (1<<3)
#define LAND_GRASS      (1<<4)

/**
 * 地图类
 * 
 * ‘#’: 边界: 不可破坏
 * ‘#’: 铁墙: 不可破坏
 * ‘^’: 土墙: 可以破坏
 * ‘Y’: 草地: 不可破坏
 * ‘~’: 河流: 不可破坏
 * 
 * 草地: 子弹 坦克
 * 河流: 子弹
 * 土墙: 都不能通过
 * 贴墙: 都不能通过
 * 边界: 都不能通过
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
    void addLand(int x, int y, int rows, int cols, int landType);
    void destroyLand(Position pos);
};


#endif // _MAP_HPP_
