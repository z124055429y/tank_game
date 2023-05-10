#include <map>
#include <utility>
#include <set>

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
    // 临时存放要删除的子弹
    std::set<Bullet*> tmpBullets;
    // 初始化子弹位置, O(n)
    Size size = map->getSize();
    std::map<int, std::list<Bullet*> > mapBullets;
    for (auto &&bullet : bullets)
    {
        Position pos = bullet->getPosition();
        int index = pos.getY() * size.getCols() + pos.getX();
        if (mapBullets.find(index) != mapBullets.end()) {
            mapBullets[index].push_back(bullet);
        } else {
            mapBullets.insert(std::make_pair(index, std::list<Bullet*>({bullet})));
        }
    }

    // 处理多子弹同位置的碰撞 O(n)
    for (auto &&bullet : bullets)
    {
        Position pos = bullet->getPosition();
        int index = pos.getY() * size.getCols() + pos.getX();
        if (mapBullets[index].size() == 1) { continue; }
        for (auto tmp : mapBullets[index])
        {
            tmpBullets.insert(tmp);
        }
        mapBullets.erase(index);
    }
    bullets.remove_if([tmpBullets](Bullet * bullet)->bool { return tmpBullets.find(bullet) != tmpBullets.end(); });

    /// TODO: 处理子弹的交错碰撞 O(n)
    for (auto &&bullet : bullets)
    {
        Position pos = bullet->getPosition();
        Position lastPos = getBulletLastPosition(bullet);
        int index = pos.getY() * size.getCols() + pos.getX();
        int lastIndex = lastPos.getY() * size.getCols() + lastPos.getX();
        
        if (mapBullets.find(lastIndex) == mapBullets.end()) continue;
        Bullet *target = mapBullets[lastIndex].front(); // 上一步已经处理了大小大于1的情况，这里大小都为1

        int bulletDir = bullet->getStatus() & MASK_DIRECTION;
        int targetDir = target->getStatus() & MASK_DIRECTION;
        int flag = bulletDir | targetDir;
        if (flag == (LEFT | RIGHT) || flag == (UP | DOWN)) {
            tmpBullets.insert({bullet, target});
            mapBullets.erase(index);
            mapBullets.erase(lastIndex);
        }
    }
    bullets.remove_if([tmpBullets](Bullet * bullet)->bool { return tmpBullets.find(bullet) != tmpBullets.end(); });
    
    
    // 检测地图和子弹的碰撞 O(n)
    for (auto &&bullet : bullets)
    {
        Position pos = bullet->getPosition();
        if ((*map)[pos.getY()][pos.getX()] == FLAG_BORDER) {
            tmpBullets.insert(bullet);
        }
    }
    bullets.remove_if([tmpBullets](Bullet * bullet)->bool { return tmpBullets.find(bullet) != tmpBullets.end(); });
    collisionBullets.insert(collisionBullets.begin(), tmpBullets.begin(), tmpBullets.end());
}

Position Detector::getBulletLastPosition(Bullet *bullet) {
    Position position = bullet->getPosition();
    int x = position.getX(), y = position.getY();
    switch (bullet->getStatus() & MASK_DIRECTION)
    {
    case LEFT:  x += 1; break;
    case RIGHT: x -= 1; break;
    case UP:    y += 1; break;
    case DOWN:  y -= 1; break;
    default: break;
    }
    position.set(x, y);
    return position;
}