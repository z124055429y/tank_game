#if !defined(_GENERATOR_HPP_)
#define _GENERATOR_HPP_

#include <list>

#include "base/detector.hpp"
#include "element/bullet.hpp"

class Generator
{
private:
    std::list<Bullet*> mBullets;
    Detector *mDetector;
public:
    Generator(/* args */);
    ~Generator();
    Detector* allocDetector(Size size);
    void freeDetector(Detector **detector);
    Bullet* allocBullet(int x, int y, int status);
    void freeBullet(Bullet *bullet);
};


#endif // _GENERATOR_HPP_
