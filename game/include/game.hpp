#if !defined(_GAME_HPP_)
#define _GAME_HPP_

#include "engine.hpp"

class Game
{
    friend void alarm_action(int signo);
private:
    bool mQuit;
    TankEngine* tankEngine;
    void render(std::list<Tank*> elements);
public:
    Game(/* args */);
    ~Game();
    void run();
    void refresh();
};

#endif // _GAME_HPP_
