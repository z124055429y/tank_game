#if !defined(_MOVE_HPP_)
#define _MOVE_HPP_

#include "base/element.hpp"

/**
 * 可以移动的元素行为
 * 
 * 思考: 是否存在临界区访问问题
*/
class Move
{
private:
    int mSpeed; // 元素速度
    int mTimer; // 计时器为0代表超时, 此时才可以移动元素
public:
    Move(int speed, int timer): mSpeed(speed), mTimer(timer) {}
    Move(int speed): Move(speed, 0) {}
    /// @brief 可移动的目标是否超时, 超时意味着可以刷新元素位置, 否则当前帧不能刷新元素位置
    /// @return 是否超时
    bool isReady() { return mTimer == 0; };
    /// @brief 每一帧都调用, 负责计时
    /// @param manual 超时时, 是否需要手动触发, (坦克需要手动, 子弹是自动的)
    void tick(bool manual);
    /// @brief 产生了手动触发的行为(eg: 按下上下左右), 刷新计时器, 只有当mTimer为0时才有效
    void action();
    /// @brief 产生元素的移动行为
    /// @param elem 要移动的元素 
    /// @param dir 移动的方向
    void move(Element *elem, int dir);

    /// 以下测试用
    int getTimer();
    int getSpeed();
};

#endif // _MOVE_HPP_