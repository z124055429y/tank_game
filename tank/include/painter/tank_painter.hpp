#if !defined(_TANK_PAINTER_CPP_)
#define _TANK_PAINTER_CPP_

#include "base/painter.hpp"
#include "element/tank.hpp"

/**
 * 坦克画笔, 绘制坦克
*/
class TankPainter
{
private:
    const int TANK_LEFT [3][3] = {{0, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    const int TANK_UP   [3][3] = {{0, 1, 0}, {1, 1, 1}, {1, 0, 1}};
    const int TANK_RIGHT[3][3] = {{1, 1, 0}, {0, 1, 1}, {1, 1, 0}};
    const int TANK_DOWN [3][3] = {{1, 0, 1}, {1, 1, 1}, {0, 1, 0}};
    char mCh;

public:
    TankPainter() : TankPainter('*') {}
    TankPainter(char ch) : mCh(ch) {}
    void draw(Tank *tank)
    {
        // 前置判断
        if (!tank)
            return;

        // 得到坦克方向的位图
        const int(*tankBitmap)[3][3] = nullptr;
        switch (tank->getStatus() & MASK_DIRECTION)
        {
        case UP:
            tankBitmap = &TANK_UP;
            break;
        case DOWN:
            tankBitmap = &TANK_DOWN;
            break;
        case LEFT:
            tankBitmap = &TANK_LEFT;
            break;
        case RIGHT:
            tankBitmap = &TANK_RIGHT;
            break;
        default:
            break;
        }
        if (!tankBitmap)
            return;

        // 通过位图绘制坦克到坦克对象的缓存
        int rows, cols;
        int **tmp = tank->getBitmap(rows, cols);
        if (rows != 3 || cols != 3)
            return;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if ((*tankBitmap)[i][j] != 0)
                {
                    tmp[i][j] = mCh;
                }
                else
                {
                    tmp[i][j] = ' ';
                }
            }
        }
    }
};

#endif // _TANK_PAINTER_CPP_
