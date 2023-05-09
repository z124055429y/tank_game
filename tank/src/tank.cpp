#include <iostream>
#include <limits.h>
#include "element/tank.hpp"

Tank::Tank(STATUS status, int hp): Element(0, 0, 3, 3, status), Move(3), mHp(hp) {}
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