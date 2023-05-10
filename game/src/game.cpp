#include <stdio.h>
#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>

#include "game.hpp"
#include "timer.hpp"
#include "handler.hpp"

void alarm_action(int signo);
void registSignal();

Game *game;
Game::Game(): mQuit(false)
{
    game = this;
    tankEngine = new TankEngine();

    registSignal();
    SystemTimer::startTimer();
    initscr();  // 初始化ncurses
    noecho();   // 无回显
    curs_set(0);// 无光标
    cbreak();      // 无行缓冲
}

Game::~Game()
{
    SystemTimer::stopTimer();
    endwin();   // 结束ncurses

    delete tankEngine;
}

void registSignal() {
    if (signal(SIGALRM, alarm_action) != 0)
    {
        perror("signal error");
        ::exit(0);
    }
}

void Game::run() {
    Tank *tank1 = new Tank(PLAYER_ID_1 | DOWN, 2);
    Tank *tank2 = new Tank(PLAYER_ID_2 | DOWN, 2);
    tank1->setPosition({3, 3});
    tank2->setPosition({9, 9});
    Map *map = new Map(20, 40);
    tankEngine->addTank(tank1);
    tankEngine->addTank(tank2);
    tankEngine->bindMap(map);
    while (!mQuit) {
        char ch = getch();
        if (ch == 'q') { mQuit = true; break; }
        // 通过输入产生命令
        int cmd = Handler::generateCommand(ch);
        if (cmd == 0) continue;
        mQuit = tankEngine->handle(cmd);
    }
    // delete tank1;
    // delete tank2;
    delete map;
}

void Game::refresh() {
    tankEngine->refresh();
}

void Game::render() {
    std::list<Element*> elements = tankEngine->getElements();
    for (auto &&element : elements)
    {
        int rows, cols;
        Position pos = element->getPosition();
        int **b = element->getBitmap(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (b[i][j] == ' ') continue;
                mvaddch(i + pos.getY(), j + pos.getX(), b[i][j]);
            }
        }
    }

    mvprintw(0, 50, "Tank count = %d", tankEngine->getTanks().size());
    mvprintw(1, 50, "Bullet count = %d", tankEngine->getBullets().size());
}

void alarm_action(int signo)
{
    // 清屏
    clear();
    // 刷新帧
    game->refresh();
    // 渲染到缓冲
    game->render();
    // 刷新缓冲
    refresh();
}