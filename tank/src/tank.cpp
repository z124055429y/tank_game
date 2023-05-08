#include <iostream>
#include <limits.h>
#include "element/tank.hpp"

Tank::Tank(STATUS status, int hp): Element(0, 0, 3, 3, status), Move(3), mHp(hp) {

}
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
    // 更改坦克位置
    dir &= MASK_DIRECTION;
    Position pos = getPosition();
    int x = pos.getX();
    int y = pos.getY();
    switch (dir)
    {
    case UP:    setPosition({x, y - 1});    break;
    case DOWN:  setPosition({x, y + 1});    break;
    case LEFT:  setPosition({x - 1, y});    break;
    case RIGHT: setPosition({x + 1, y});    break;
    default: break;
    }
    mStatus = (mStatus & ~MASK_DIRECTION) | dir;
    // 刷新定时器
    action();
}