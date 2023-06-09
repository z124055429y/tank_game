#include "base/generator.hpp"

Generator::Generator(/* args */): mDetector(nullptr) {}
Generator::~Generator() {}

Detector* Generator::allocDetector(Size size) {
    if (mDetector != nullptr) {
        freeDetector(&mDetector);
    }
    Detector *detector = new Detector(size);
    return detector;
}

void Generator::freeDetector(Detector **detector) {
    if (*detector == nullptr) return;
    delete *detector;
    *detector = nullptr;
}


Bullet* Generator::allocBullet(int x, int y, STATUS status, int damage, int speed) {
    Bullet *bullet = new Bullet(x, y, status, damage, speed);
    mBullets.push_back(bullet);
    return bullet;
}

void Generator::freeBullet(Bullet *bullet) {
    mBullets.remove(bullet);
    delete bullet;
}

void Generator::allocTank() {

}

void Generator::freeTank(Tank *tank) {
    mTanks.remove(tank);
    delete tank;
}

