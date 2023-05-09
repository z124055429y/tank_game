#if !defined(_TIMER_HPP_)
#define _TIMER_HPP_

/**
 * 计时器, 定时发出信号触发绘制
 * 
 * 1s 25帧
*/
class Timer
{
private:
    
public:
    static bool startTimer();
    static void stopTimer();
};

#endif // _TIMER_HPP_
