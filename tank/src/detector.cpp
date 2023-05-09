#include "base/detector.hpp"
#include "base/allocate.hpp"

Detector::Detector(Size size): mSize(size)
{
    pBitmap = allocSpace(size.getRows(), size.getCols());
}

Detector::~Detector()
{
    freeSpace(pBitmap, mSize.getRows(), mSize.getCols());
}
    
int Detector::touchCheck(Element *origin, std::list<Touch*> constraints) {
    int flag = 0;
    // 检测当前元素和所有可接触元素的接触情况
    for (auto &&constraint : constraints)
    {
        int rows, cols;
        int tmp = constraint->touch(origin);
        flag |= tmp;
    }
    return flag;
}

void Detector::collisionCheck(std::list<Tank*> &tanks, std::list<Bullet*> &bullets, Map *map, std::list<Tank*> &collisionTanks, std::list<Bullet*> &collisionBullets) {
    for (auto &&bullet : bullets)
    {
        Position pos = bullet->getPosition();
        if ((*map)[pos.getY()][pos.getX()] == FLAG_BORDER) {
            collisionBullets.push_back(bullet);
        }
    }
}