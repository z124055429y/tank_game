#include "action/move.hpp"

void Move::tick(bool manual) {
    if (manual) {
        if (mTimer > 0) {
            mTimer--;
        }
    } else {
        if (mTimer > 0) {
            mTimer--;
        } else {
            mTimer = mSpeed;
        }
    }
}

void Move::action() {
    if (mTimer != 0) return;// 未超时, 无效行为
    mTimer = mSpeed;
}

void Move::move(Element *elem, int dir) {
    dir &= MASK_DIRECTION;
    Position pos = elem->getPosition();
    int x = pos.getX();
    int y = pos.getY();
    switch (dir)
    {
    case UP:    elem->setPosition({x, y - 1});    break;
    case DOWN:  elem->setPosition({x, y + 1});    break;
    case LEFT:  elem->setPosition({x - 1, y});    break;
    case RIGHT: elem->setPosition({x + 1, y});    break;
    default: break;
    }
}

int Move::getTimer() {
    return mTimer;
}

int Move::getSpeed() {
    return mSpeed;
}