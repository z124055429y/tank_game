#if !defined(_ENGINE_HPP_)
#define _ENGINE_HPP_


#include <list>
#include <set>
#include <vector>

#include "element/tank.hpp"
#include "painter/tank_painter.hpp"

/**
 * 坦克游戏逻辑处理
*/
class TankEngine
{
private:
    std::vector<int>    mCmds;          // 存放每个周期的命令
    std::list<Tank*>    mTanks;         // 坦克列表
    std::list<Tank*>    mTmpTanks;      // 临时坦克列表
    TankPainter p1;
    void updateTank();
    int getTankAction(Tank* tank);
    bool moveTank(Tank *tank, int action);
    void drawTank(Tank *tank);

    void tickMoveElement();
public:
    TankEngine();
    ~TankEngine();
    /// @brief 每一帧刷新
    void refresh();
    /// @brief 处理输入命令
    /// @param cmd 0~3位表示方向（有且只有一个有效），4位表示开火, 8~15位表示元素标志
    /// @return 是否退出游戏
    bool handle(int cmd);
    /// @brief 获取绘制元素
    /// @return
    std::list<Element*> getElements();

    /// 以下代码主要用来测试
    void addTank(Tank *tank);
    std::list<Tank*>    getTanks();
    std::vector<int>    getCmd();
};

#endif // _ENGINE_HPP_
