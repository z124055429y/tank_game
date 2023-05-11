#include <stdio.h>
#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>

#include "game.hpp"
#include "timer.hpp"

void alarm_action(int signo);
void registSignal();

Game *game;
Game::Game(): mQuit(false)
{
    srand(time(NULL));
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
    tankEngine->init();
    
    while (!mQuit) {
        char ch = getch();
        if (ch == 'q') { mQuit = true; break; }
        // 通过输入产生命令
        mQuit = tankEngine->input(ch);
    }

    tankEngine->destroy();
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