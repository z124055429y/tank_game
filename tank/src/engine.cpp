#include <ctime>
#include <cstdlib>

#include "engine.hpp"

TankEngine::TankEngine(): mCmds(10, 0), mMap(nullptr), detector(nullptr) {}
TankEngine::~TankEngine() {}

bool TankEngine::handle(int command) {
    int playerId = command & MASK_PLAYER_ID;
    // 如果对应玩家的方向命令未使用, 无效命令
    int playerIndex = -1;
    switch (playerId)
    {
    case PLAYER_ID_1: playerIndex = 0; break;
    case PLAYER_ID_2: playerIndex = 1; break;
    default: break;
    }
    // 没有命中
    if (playerIndex == -1) return false;
    // 命中后, 当前命令是更改方向, 但已经有方向, 不更新命令
    if (mCmds[playerIndex] & MASK_DIRECTION && command & MASK_DIRECTION) return false;
    // 更新命令
    mCmds[playerIndex] |= command;

    return false;
}

void TankEngine::refresh() {
    // 更新坦克
    updateTank();
    // 更新子弹
    updateBullet();
    // 更新地图
    updateMap();
    // 处理碰撞
    handleCollision();
    // tick可移动的元素
    tickMoveElement();
}

void TankEngine::tickMoveElement() {
    for (auto &&tank : mTanks)
    {
        tank->tick(true);
    }
    for (auto &&bullet : mBullets)
    {
        bullet->tick(false);
    }
}

/// 坦克部分开始

int TankEngine::getTankAction(Tank *tank) {
    int action = 0;
    int status = tank->getStatus();
    int index = -1;
    switch (status & MASK_PLAYER_ID)
    {
    case PLAYER_ID_1: index = 0; break;
    case PLAYER_ID_2: index = 1; break;
    }
    if (status & MASK_PLAYER_ID) {
        action = (mCmds[index] & MASK_ACTION);
        mCmds[index] &= ~MASK_ACTION;
    } else {
        int curDir = (status & MASK_DIRECTION);
        if (tank->isFireReady()) {
            action |= (rand() % 5) ? NONE : (rand() % 2 ? curDir : (1 << rand() % 4));
        }
        if (tank->isReady()) {
            action |= (rand() % 5) ? NONE : FIRE;
        }
    }
    return action;
}

bool TankEngine::moveTank(Tank *tank, int action) {
    int flag = 0;
    if (detector != nullptr && mMap != nullptr) {
        std::list<Touch*> constraints;
        // 添加地图约束
        constraints.push_back(mMap);
        // 添加坦克约束
        for (auto &&tank : mTanks)
        {
            constraints.push_back(tank);
        }
        flag = detector->touchCheck(tank, constraints);
    }
    
    
    if (flag & MASK_DIRECTION & action) {
        if (tank->getStatus() & MASK_DIRECTION & action) {
            return false;
        } else {
            tank->setDirection(action);
            return true;
        }
    }
    tank->move(action);

    // 刷新定时器
    tank->reset();
    return true;
}

void TankEngine::fireBullet(Tank *tank, int action) {
    // 行为中没有开火，跳过
    if ((action & FIRE) == 0) return;
    // 坦克没有准备好开火
    if (!tank->isFireReady()) return;
    
    tank->fireReset();
    Size size = tank->getSize();
    Position pos = tank->getPosition();
    int status = tank->getStatus();
    int x = pos.getX() + size.getCols() / 2;
    int y = pos.getY() + size.getRows() / 2;
    int offsetX = size.getCols() / 2 + 1;
    int offsetY = size.getRows() / 2 + 1;
    switch (status & MASK_DIRECTION)
    {
    case UP:    y += -offsetX; break;
    case DOWN:  y +=  offsetX; break;
    case LEFT:  x += -offsetY; break;
    case RIGHT: x +=  offsetY; break;
    default: return;
    }
    Bullet *bullet = generator.allocBullet(x, y, status & MASK_DIRECTION);
    drawBullet(bullet);
    mBullets.push_back(bullet);
}

void TankEngine::drawTank(Tank *tank) {
    tankPainter.draw(tank);
}

void TankEngine::updateTank() {
    // 获取需要操作的坦克
    for (auto &&tank: mTanks)
    {
        if (!tank->isReady()) continue;
        mTmpTanks.push_back(tank);
    }

    // 循环更新坦克
    for (auto &&tank : mTmpTanks)
    {
        // 获取行为
        int action = getTankAction(tank);
        // 移动坦克
        bool isUpdate = false;
        isUpdate = moveTank(tank, action);
        // 绘制坦克
        if (isUpdate) { drawTank(tank); }
        // 开火
        fireBullet(tank, action);
    }

    // 清空操作的坦克列表
    mTmpTanks.clear();
}

/// 坦克部分结束

/// 子弹部分开始

void TankEngine::moveBullet(Bullet *bullet) {
    int action = bullet->getStatus() & MASK_DIRECTION;
    bullet->move(action);
}

void TankEngine::drawBullet(Bullet *bullet) {
    bulletPainter.draw(bullet);
}

void TankEngine::updateBullet() {
    // 获取需要更新的子弹
    for (auto &&bullet : mBullets)
    {
        if (!bullet->isReady()) continue;
        mTmpBullets.push_back(bullet);
    }
    
    // 刷新子弹位置
    for (auto &&bullet : mTmpBullets)
    {
        moveBullet(bullet);
    }

    mTmpBullets.clear();
}

/// 子弹部分结束

/// 地图部分开始

void TankEngine::updateMap() {
    if (mMap == nullptr) return;
    mapPainter.draw(mMap);
}

/// 地图部分结束

void TankEngine::handleCollision() {
    if (detector == nullptr || mMap == nullptr) return;
    detector->collisionCheck(mTanks, mBullets, mMap, mTmpTanks, mTmpBullets);
    for (auto &&bullet : mTmpBullets)
    {
        generator.freeBullet(bullet);
    }
    for (auto &&tank : mTmpTanks)
    {
        generator.freeTank(tank);
    }

    mTmpTanks.clear();
    mTmpBullets.clear();
}

std::list<Tank*> TankEngine::getTanks() {
    return mTanks;
}

std::list<Bullet*> TankEngine::getBullets() {
    return mBullets;
}

void TankEngine::addTank(Tank *tank) {
    mTanks.push_back(tank);
}

void TankEngine::addBullet(Bullet *bullet) {
    mBullets.push_back(bullet);
}

void TankEngine::bindMap(Map *map) {
    mMap = map;
    Size size = mMap->getSize();
    detector = generator.allocDetector(size);
}

std::list<Element*> TankEngine::getElements() {
    std::list<Element*> elems;
    if (mMap != nullptr) {
        elems.push_back(mMap);
    }
    for (auto &&tank : mTanks)
    {
        elems.push_back(tank);
    }
    for (auto &&bullet : mBullets)
    {
        elems.push_back(bullet);
    }

    return elems;
}

std::vector<int> TankEngine::getCmd() {
    return mCmds;
}