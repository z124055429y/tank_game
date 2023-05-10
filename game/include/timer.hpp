#if !defined(_SYSTEM_TIMER_HPP_)
#define _SYSTEM_TIMER_HPP_

/**
 * 计时器, 定时发出信号触发绘制
 * 
 * 1s 25帧
*/
class SystemTimer
{
private:
    
public:
    static bool startTimer();
    static void stopTimer();
};

#endif // _SYSTEM_TIMER_HPP_
