#include <sys/time.h>

#include "timer.hpp"

void Timer::stopTimer()
{
    struct itimerval timer;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
}

bool Timer::startTimer()
{
    struct itimerval timer;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 40 * 1000;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 40 * 1000;
    return setitimer(ITIMER_REAL, &timer, NULL) == 0;
}