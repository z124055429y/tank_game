#include <stdio.h>
#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>

#include "element/tank.hpp"
#include "painter/tank_painter.hpp"
#include "element/map.hpp"
#include "painter/map_painter.hpp"

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
    Timer::startTimer();
    initscr();  // 初始化ncurses
    noecho();   // 无回显
    curs_set(0);// 无光标
    raw();      // 无行缓冲
}

Game::~Game()
{
    Timer::stopTimer();
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
    Tank *tank = new Tank(PLAYER_ID_1 | DOWN, 2);
    tankEngine->addTank(tank);
    while (!mQuit) {
        char ch = getch();
        if (ch == 'q') {
            mQuit = true;
            break;
        }
        int cmd = Handler::getcmd(ch);
        mQuit = tankEngine->handle(cmd);
    }

    // 一定要先refresh，再wrefresh
    // Map map(20,40);
    // MapPainter painter;
    // painter.draw(&map);

    // refresh();
    // WINDOW *win = newwin(20,40,5,5);

    // int rows, cols;
    // int **b = map.getBitmap(rows, cols);
    // for (int i = 0; i < rows; i++)
    // {
    //     for (int j = 0; j < cols; j++)
    //     {
    //         mvwaddch(win, i, j, b[i][j]);
    //     }
    // }

    // wborder(win, '#','#','#','#','#','#','#','#');
    // mvwprintw(win, 1, 1, "Hello World1");

    // wrefresh(win);
    // delwin(win);

    
    // Tank *tank = new Tank(RIGHT, 3);
    // TankPainter *painter = new TankPainter();
    // painter->draw(tank);
    // int row, col;
    // int **b = tank->getBitmap(row,col);
    // for (int i = 0; i < row; i++)
    // {
    //     for (int j = 0; j < col; j++)
    //     {
    //         mvaddch(i, j, b[i][j]);
    //     }
    // }
    // refresh();
}

void Game::refresh() {
    tankEngine->refresh();
    std::list<Tank*> tanks = tankEngine->getTanks();
    render(tanks);
}

void Game::render(std::list<Tank*> elements) {
    printw("size = %d\n", elements.size());
    for (auto &&element : elements)
    {
        int rows, cols;
        Position pos = element->getPosition();
        int **b = element->getBitmap(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                mvaddch(i + pos.getY(), j + pos.getX(), b[i][j]);
            }
        }
    }
}

void alarm_action(int signo)
{
    clear();
    game->refresh();
    refresh();
}