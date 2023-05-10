#include "base/timer.hpp"

void Timer::tick(bool manual) {
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
