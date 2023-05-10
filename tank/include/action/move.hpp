#if !defined(_MOVE_HPP_)
#define _MOVE_HPP_

#include "base/element.hpp"
#include "base/timer.hpp"

/**
 * 可以移动的元素行为
 * 
 * 思考: 是否存在临界区访问问题
*/
class Move
{
private:
    Timer mTimer;
public:
    Move(int speed, int timer): mTimer(speed, timer) {}
    Move(int speed): Move(speed, 0) {}
    bool isReady() { return mTimer.isReady(); };
    virtual void tick(bool manual) { mTimer.tick(manual); }
    /// @brief 产生了手动触发的行为(eg: 按下上下左右), 刷新计时器, 只有当mTimer为0时才有效
    void reset() { mTimer.reset(); };
    /// @brief 产生元素的移动行为
    /// @param elem 要移动的元素 
    /// @param dir 移动的方向
    void move(Element *elem, int dir);

    /// 以下测试用
    int getTimer() { return mTimer.getTimer(); }
    int getSpeed() { return mTimer.getSpeed(); }
};

#endif // _MOVE_HPP_