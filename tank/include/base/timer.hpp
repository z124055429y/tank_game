#if !defined(_TIMER_HPP_)
#define _TIMER_HPP_

class Timer
{
private:
    int mSpeed; // 元素速度
    int mTimer; // 计时器为0代表超时, 此时才可以移动元素
public:
    Timer(int speed, int timer): mSpeed(speed), mTimer(timer) {}
    /// @brief 是否超时, 超时意味着可以刷新元素位置, 否则当前帧不能刷新元素位置
    /// @return 是否超时
    bool isReady() { return mTimer == 0; };
    /// @brief 每一帧都调用, 负责计时
    /// @param manual 超时时, 是否需要手动触发, (坦克需要手动, 子弹是自动的)
    void tick(bool manual);
    void reset() { mTimer = mSpeed; }
    
    int getTimer() { return mTimer; }
    int getSpeed() { return mSpeed; }
};



#endif // _TIMER_HPP_
