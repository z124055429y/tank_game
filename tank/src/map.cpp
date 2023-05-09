#include "element/map.hpp"

Map::Map(int rows, int cols): Element(rows, cols)
{
    mFlag = allocSpace(rows, cols);
    clear();
    initBorder();
}

Map::~Map()
{
    freeSpace(mFlag, mSize.getRows(), mSize.getCols());
}

int* Map::operator[](const int pos) {
    return mFlag[pos];
}

void Map::clear() {
    int rows = mSize.getRows();
    int cols = mSize.getCols();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mFlag[i][j] = 0;
        }
    }
}

void Map::initBorder() {
    int rows = mSize.getRows();
    int cols = mSize.getCols();
    
    // 初始化边界
    for (int i = 0; i < rows; i++)
    {
        mFlag[i][0] = (mFlag[i][0] & MASK_LAND) | FLAG_BORDER;
        mFlag[i][cols - 1] = (mFlag[i][cols - 1] & MASK_LAND) | FLAG_BORDER;
    }
    for (int i = 0; i < cols; i++)
    {
        mFlag[0][i] = (mFlag[0][i] & MASK_LAND) | FLAG_BORDER;
        mFlag[rows - 1][i] = (mFlag[rows - 1][i] & MASK_LAND) | FLAG_BORDER;
    }
    
}

int Map::touch(Element *origin) {
    int flag = 0;
    Position pos = origin->getPosition();
    Size size = origin->getSize();
    int touchFlag = FLAG_BORDER;
    for (size_t i = 0; i < size.getRows(); i++) {
        int x = pos.getX() - 1, y = pos.getY() + i;
        if (mFlag[y][x] & touchFlag) {
            flag |= LEFT;
            break; 
        }
    }
    for (size_t i = 0; i < size.getRows(); i++) {
        int x = pos.getX() + size.getCols(), y = pos.getY() + i;
        if (mFlag[y][x] & touchFlag) { 
            flag |= RIGHT;
            break;
        }
    }
    for (size_t i = 0; i < size.getCols(); i++) {
        int x = pos.getX() + i,y = pos.getY() - 1;
        if (mFlag[y][x] & touchFlag) {
            flag |= UP;
            break;
        }
    }
    for (size_t i = 0; i < size.getCols(); i++) {
        int x = pos.getX() + i,y = pos.getY() + size.getRows();
        if (mFlag[y][x] & touchFlag) {
            flag |= DOWN;
            break;
        }
    }
    return flag;
}