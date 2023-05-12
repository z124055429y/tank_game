#if !defined(_GAME_HPP_)
#define _GAME_HPP_

#include "engine.hpp"

class Game
{
    friend void alarm_action(int signo);
private:
    bool mQuit;
    TankEngine* tankEngine;
    /// @brief 获取每个元素并刷新到curses缓冲中
    void render();
    /// @brief 刷新帧数据
    void refresh();
    int ret = -1;
public:
    Game(/* args */);
    ~Game();
    void run();
};

#endif // _GAME_HPP_
