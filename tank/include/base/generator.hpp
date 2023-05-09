#if !defined(_GENERATOR_HPP_)
#define _GENERATOR_HPP_

#include <list>

#include "element/bullet.hpp"

class Generator
{
private:
    std::list<Bullet*> mBullets;
public:
    Generator(/* args */);
    ~Generator();
    Bullet* allocBullet(int x, int y, int status);
    void freeBullet(Bullet *bullet);
};


#endif // _GENERATOR_HPP_
