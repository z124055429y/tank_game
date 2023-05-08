#include "engine.hpp"

int checkTouch(Tank *tank);

TankEngine::TankEngine()
{
}

TankEngine::~TankEngine()
{
    for (auto &&tank : mTanks)
    {
        delete tank;
    }
    mTanks.clear();
}

void TankEngine::refresh() {
    // 通过命令尝试操作坦克
    updateTank();
}

void TankEngine::updateTank() {
    // 找出当前帧中需要操作的坦克
    for (auto &&tank: mTanks)
    {
        // 超时，加入临时队列
        if (tank->isDirty()) {
            mTmpTanks.push_back(tank);
        }
    }

    // 解析命令
    int player1Action = 0;
    int player2Action = 0;
    parseCommand(player1Action, player2Action);

    // 循环更新坦克
    for (auto &&tank : mTmpTanks)
    {
        // 获取行为
        int action = 0;
        switch (tank->getDirection() & MASK_PLAYER_ID)
        {
        case PLAYER_ID_1: {
            mCmds.remove_if([](int n){ return (n & PLAYER_ID_1) != 0; });
            action = player1Action;
            break;
        }
        }
        // 检查接触情况
        int flag = checkTouch(tank);
        if (flag & MASK_DIRECTION & action) continue;
        
        // 移动坦克
        tank->move(action);

        // 绘制坦克
        p1.draw(tank);
    }
    for (auto &&tank : mTanks)
    {
        tank->tick(true);
    }
    mTmpTanks.clear();
}

bool TankEngine::handle(int command) {
    int playerId = command & MASK_PLAYER_ID;
    // 如果对应玩家的方向命令未使用，无效命令
    for (auto &&cmd : mCmds)
    {
        if (cmd & playerId && cmd & MASK_ACTION) return false;
        if (cmd == command) return false;
    }
    // 加入命令队列中
    mCmds.push_back(command);
    return false;
}

void TankEngine::parseCommand(int &p1, int &p2) {
    for (auto &&cmd : mCmds)
    {
        switch (cmd & MASK_PLAYER_ID)
        {
        case PLAYER_ID_1: p1 |= cmd & MASK_ACTION; break;
        case PLAYER_ID_2: p2 |= cmd & MASK_ACTION; break;
        default: break;
        }
    }
}

int checkTouch(Tank *tank) {
    int flag = 0;
    /*
    // if (mMap == nullptr) return flag;

    char **map = mMap->getMap();
    Size size = tank->getSize();
    Position pos = tank->getPosition();
    
    for (size_t i = 0; i < size.getRows(); i++) {
        int x = pos.getX() - 1, y = pos.getY() + i;
        if (map[y][x] == WALL_CHAR) {
            flag |= LEFT;
            break;
        }
    }
    for (size_t i = 0; i < size.getRows(); i++) {
        int x = pos.getX() + size.getCols(), y = pos.getY() + i;
        if (map[y][x] == WALL_CHAR) {
            flag |= RIGHT;
            break;
        }
    }
    for (size_t i = 0; i < size.getCols(); i++) {
        int x = pos.getX() + i,y = pos.getY() - 1;
        if (map[y][x] == WALL_CHAR) {
            flag |= UP;
            break;
        }
    }
    for (size_t i = 0; i < size.getCols(); i++) {
        int x = pos.getX() + i,y = pos.getY() + size.getRows();
        if (map[y][x] == WALL_CHAR) {
            flag |= DOWN;
            break;
        }
    }
    */
    
    return flag;
}

std::list<Tank*> TankEngine::getTanks() {
    return mTanks;
}

void TankEngine::addTank(Tank *tank) {
    mTanks.push_back(tank);
}

std::list<int> TankEngine::getCmd() {
    return mCmds;
}