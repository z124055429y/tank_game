#include "engine.hpp"

int checkTouch(Tank *tank);

TankEngine::TankEngine(): mCmds(10, 0) { }

TankEngine::~TankEngine() { }

void TankEngine::refresh() {
    // 通过命令尝试操作坦克
    updateTank();
    // tick可移动的元素
    tickMoveElement();
}

void TankEngine::tickMoveElement() {
    for (auto &&tank : mTanks)
    {
        tank->tick(true);
    }
}

int TankEngine::getTankAction(Tank *tank) {
    int action = 0;
    int status = tank->getStatus();
    int index = -1;
    switch (status & MASK_PLAYER_ID)
    {
    case PLAYER_ID_1: index = 0; break;
    case PLAYER_ID_2: index = 1; break;
    }
    if (index == -1) return 0;
    action = (mCmds[index] & MASK_ACTION);
    mCmds[index] &= ~MASK_ACTION;
    return action;
}

bool TankEngine::moveTank(Tank *tank, int action) {
    int flag = 0;
    if (flag & MASK_DIRECTION & action) return false;
    tank->move(action);
    return true;
}

void TankEngine::drawTank(Tank *tank) {
    p1.draw(tank);
}

void TankEngine::updateTank() {
    // 获取需要操作的坦克
    for (auto &&tank: mTanks)
    {
        if (!tank->isDirty()) continue;
        mTmpTanks.push_back(tank);
    }

    // 循环更新坦克
    for (auto &&tank : mTmpTanks)
    {
        // 获取行为
        int action = getTankAction(tank);
        // 操作坦克
        bool isUpdate = false;
        isUpdate = moveTank(tank, action);
        // 绘制坦克
        if (!isUpdate) continue;
        drawTank(tank);
    }

    // 清空操作的坦克列表
    mTmpTanks.clear();
}

bool TankEngine::handle(int command) {
    int playerId = command & MASK_PLAYER_ID;
    // 如果对应玩家的方向命令未使用，无效命令
    int playerIndex = -1;
    switch (playerId)
    {
    case PLAYER_ID_1: playerIndex = 0; break;
    case PLAYER_ID_2: playerIndex = 1; break;
    default: break;
    }
    // 没有命中
    if (playerIndex == -1) return false;
    // 命中后，当前命令是更改方向，但已经有方向, 不更新命令
    if (mCmds[playerIndex] & MASK_DIRECTION && command & MASK_DIRECTION) return false;
    // 更新命令
    mCmds[playerIndex] |= command;

    return false;
}

std::list<Tank*> TankEngine::getTanks() {
    return mTanks;
}

void TankEngine::addTank(Tank *tank) {
    mTanks.push_back(tank);
}

std::list<Element*> TankEngine::getElements() {
    std::list<Element*> elems;
    for (auto &&tank : mTanks)
    {
        elems.push_back(tank);
    }
    return elems;
}

std::vector<int> TankEngine::getCmd() {
    return mCmds;
}