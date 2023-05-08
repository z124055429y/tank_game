#if !defined(_ENGINE_HPP_)
#define _ENGINE_HPP_


#include <list>
#include <set>

#include "element/tank.hpp"
#include "painter/tank_painter.hpp"

/**
 * 坦克游戏逻辑处理
*/
class TankEngine
{
private:
    std::list<int>      mCmds;      // 存放每个周期的命令
    std::list<Tank*>    mTanks;     // 坦克列表
    std::list<Tank*>    mTmpTanks;  // 临时坦克列表
    TankPainter p1;
    void updateTank();
    void parseCommand(int &p1, int &p2);
public:
    TankEngine();
    ~TankEngine();
    void refresh();
    /// @brief 处理输入命令
    /// @param cmd 0~3位表示方向（有且只有一个有效），4位表示开火, 8~15位表示玩家标志
    /// @return 是否退出游戏
    bool handle(int cmd);
    std::list<Tank*> getTanks();
    void addTank(Tank *tank);
    std::list<int> getCmd();
};

#endif // _ENGINE_HPP_
