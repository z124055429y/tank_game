#if !defined(_DETECTOR_HPP_)
#define _DETECTOR_HPP_

#include <list>
#include "base/size.hpp"
#include "base/element.hpp"
#include "action/touch.hpp"
#include "element/tank.hpp"
#include "element/bullet.hpp"
#include "element/map.hpp"

class Detector
{
private:
    Size mSize;
    int **pBitmap;
    Position getBulletLastPosition(Bullet *bullet);
public:
    Detector(Size size);
    ~Detector();
    int touchCheck(Element *element, std::list<Touch*> constraints);
    /// @brief 碰撞检测
    void collisionCheck(std::list<Tank*> tanks, std::list<Bullet*> bullets, Map *map,
                        std::list<Tank*> &collisionTanks, std::list<Bullet*> &collisionBullets);
};


#endif // _DETECTOR_HPP_
