#include <iostream>
#include <limits.h>
#include "element/tank.hpp"

Tank::Tank(STATUS status, int hp, int damage, int speed, int bulletSpeed): 
    Element(0, 0, 3, 3, status), Move(speed), mFireTimer(bulletSpeed + 1, 0), 
    mHp(hp), mBulletDamage(damage), mBulletSpeed(bulletSpeed) {}
Tank::~Tank() {}

bool Tank::isDead() {
    return mHp == 0;
}

void Tank::addHp(int plusHp) {
    long long tmp = (long long)mHp + plusHp;
    mHp = (tmp >= INT_MAX) ? INT_MAX: tmp;
}

void Tank::minusHp(int minusHp) {
    long long tmp = (long long)mHp - minusHp;
    mHp = (tmp <= 0) ? 0: tmp;
}

void Tank::move(int dir) {
    if ((dir & MASK_DIRECTION) == 0) return;
    // 更改坦克位置
    Move::move(this, dir);
    // 更改坦克方向
    mStatus &= ~MASK_DIRECTION;
    mStatus |= dir;
}

void Tank::tick(bool manual) {
    mFireTimer.tick(manual);
    Move::tick(manual);
}

int Tank::touch(Element *origin) {
    // 判断origin四个方向是否和this接触, 一个方向满足接触条件，另一方向产生重叠，才被视为接触
    int flag = 0;
    Position originPos = origin->getPosition();
    Size originSize = origin->getSize();
    bool up     = originPos.getY() - mPos.getY() == mSize.getRows();
    bool down   = originPos.getY() - mPos.getY() == -originSize.getRows();
    bool left   = originPos.getX() - mPos.getX() == mSize.getCols();
    bool right  = originPos.getX() - mPos.getX() == -originSize.getCols();
    bool verticalCollapse =     originPos.getY() - mPos.getY() < mSize.getRows() && originPos.getY() - mPos.getY() > -originSize.getRows();
    bool horizentalCollapse =   originPos.getX() - mPos.getX() < mSize.getCols() && originPos.getX() - mPos.getX() > -originSize.getCols();
    if (up && horizentalCollapse) { flag |= UP; }
    if (down && horizentalCollapse) { flag |= DOWN; }
    if (left && verticalCollapse) { flag |= LEFT; }
    if (right && verticalCollapse) { flag |= RIGHT; }
    return flag;
}