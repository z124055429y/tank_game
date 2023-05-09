#include "base/generator.hpp"

Generator::Generator(/* args */)
{
}

Generator::~Generator()
{
}

Bullet* Generator::allocBullet(int x, int y, int status) {
    Bullet *bullet = new Bullet(x, y, status);
    mBullets.push_back(bullet);
    return bullet;
}

void Generator::freeBullet(Bullet *bullet) {
    mBullets.remove(bullet);
    delete bullet;
}

