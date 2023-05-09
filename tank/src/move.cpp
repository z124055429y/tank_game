#include "action/move.hpp"

void Move::tick(bool manual) {
    if (mTimer != 0) {      // 未超时
        mTimer--;
    } else if (!manual) {   // 超时，自动刷新
        mTimer = mSpeed;
    } else {                // 超时，手动刷新
        mTimer = 0;
    }
}

void Move::action() {
    if (mTimer != 0) return;// 未超时，无效行为
    mTimer = mSpeed;
}

int Move::getTimer() {
    return mTimer;
}

int Move::getSpeed() {
    return mSpeed;
}