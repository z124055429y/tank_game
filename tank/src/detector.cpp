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

void Detector::collisionCheck(std::list<Tank*> &tanks, std::list<Bullet*> &bullets, Map *map, 
        std::list<Tank*> &collisionTanks, std::list<Bullet*> &collisionBullets, State *state) {
    // 临时存放要删除的元素
    std::set<Bullet*> tmpBullets;
    std::set<Tank*> tmpTanks;
    // 地图大小
    Size size = map->getSize();

    // 缓存坦克位置
    fillSpace(pBitmap, mSize.getRows(), mSize.getCols(), -1);
    for (auto &&tank : tanks)
    {
        Position pos = tank->getPosition();
        int index = pos.getY() * size.getCols() + pos.getX();
        Size tankSize = tank->getSize();
        for (int i = 0; i < tankSize.getRows(); i++)
        {
            for (int j = 0; j < tankSize.getCols(); j++)
            {
                pBitmap[i + pos.getY()][j + pos.getX()] = index;
            }
        }
    }

    // 初始化元素索引 O(n), 思考: 代码形式上的多重循环是否就意味着时间复杂度的次方（明确问题规模和循环是否有关系）
    std::map<int, std::list<Bullet*> > mapBullets;
    std::map<int, Tank*> mapTanks;
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
    for (auto &&tank : tanks)
    {
        Position pos = tank->getPosition();
        int index = pos.getY() * size.getCols() + pos.getX();
        mapTanks.insert(std::make_pair(index, tank));
    }

    // 处理多子弹同位置的碰撞 O(n)
    for (auto &&bullet : bullets)
    {
        Position pos = bullet->getPosition();

        // 如果当前碰撞位置恰好是坦克位置, 不作为子弹的碰撞处理（视为子弹和坦克碰撞）
        if (pBitmap[pos.getY()][pos.getX()] != -1) continue;

        // 同位置只有一颗子弹, 不处理
        int index = pos.getY() * size.getCols() + pos.getX();
        if (mapBullets[index].size() == 1) { continue; }
        for (auto tmp : mapBullets[index])
        {
            tmpBullets.insert(tmp);
        }
        mapBullets.erase(index);
    }
    bullets.remove_if([tmpBullets](Bullet * bullet)->bool { return tmpBullets.find(bullet) != tmpBullets.end(); });

    /// 处理子弹的交错碰撞 O(n)
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
    
    // 处理子弹和坦克的碰撞 O(n)
    for (auto &&bullet : bullets)
    {
        Position bulletPos = bullet->getPosition();
        int x = bulletPos.getX(), y = bulletPos.getY();
        if (pBitmap[y][x] == -1) continue;

        tmpBullets.insert(bullet);

        int tankIndex = pBitmap[y][x];
        Tank *tank = mapTanks[tankIndex];
        int hp = tank->getHp();
        int damage = bullet->getDamage();
        if (hp > damage) {
            tank->minusHp(damage);
        } else {
            if (state != nullptr) {
                updateScore(bullet, 10, state);
            }
            tmpTanks.insert(tank);
        }

        int bulletIndex = bulletPos.getY() * size.getCols() + bulletPos.getX();
        mapBullets[bulletIndex].remove(bullet);
        if (mapBullets[bulletIndex].size() == 0) {
            mapBullets.erase(bulletIndex);
        }
    }
    tanks.remove_if([tmpTanks](Tank *tank)->bool { return tmpTanks.find(tank) != tmpTanks.end(); });
    bullets.remove_if([tmpBullets](Bullet *bullet)->bool { return tmpBullets.find(bullet) != tmpBullets.end(); });
    
    // 处理地图和子弹的碰撞 O(n)
    for (auto &&bullet : bullets)
    {
        Position pos = bullet->getPosition();
        int landType = (*map)[pos.getY()][pos.getX()];
        if (landType == LAND_BORDER || landType == LAND_IRON_WALL || landType == LAND_MUD_WALL) {
            tmpBullets.insert(bullet);
            if (landType == LAND_MUD_WALL) {
                map->destroyLand(pos);
            }
        }
    }
    bullets.remove_if([tmpBullets](Bullet * bullet)->bool { return tmpBullets.find(bullet) != tmpBullets.end(); });
    
    collisionBullets.insert(collisionBullets.begin(), tmpBullets.begin(), tmpBullets.end());
    collisionTanks.insert(collisionTanks.begin(), tmpTanks.begin(), tmpTanks.end());
}

void Detector::updateScore(Bullet* bullet, int score, State *state) {
    int playerIndex = -1;
    switch (bullet->getStatus() & MASK_PLAYER_ID)
    {
    case PLAYER_ID_1: playerIndex = 0; break;
    case PLAYER_ID_2: playerIndex = 1; break;
    default: break;
    }
    if (playerIndex == -1) return;
    state->addScore(playerIndex, score);
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