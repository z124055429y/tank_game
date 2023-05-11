#if !defined(_GENERATOR_HPP_)
#define _GENERATOR_HPP_

#include <list>

#include "base/detector.hpp"
#include "element/bullet.hpp"

/**
 * 生成器
 * 
 * 优化: 可以用set容器代替list容器, 进而更快的删除列表
*/
class Generator
{
private:
    std::list<Bullet*>  mBullets;
    std::list<Tank*>    mTanks;
    Detector *mDetector;
public:
    Generator(/* args */);
    ~Generator();
    Detector* allocDetector(Size size);
    void freeDetector(Detector **detector);
    Bullet* allocBullet(int x, int y, STATUS status, int damage, int speed);
    void freeBullet(Bullet *bullet);
    void allocTank();
    void freeTank(Tank *tank);
};


#endif // _GENERATOR_HPP_
