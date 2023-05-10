#if !defined(_ENGINE_HPP_)
#define _ENGINE_HPP_


#include <list>
#include <set>
#include <vector>

#include "base/generator.hpp"
#include "base/detector.hpp"
#include "element/tank.hpp"
#include "element/bullet.hpp"
#include "element/map.hpp"
#include "element/state.hpp"
#include "painter/tank_painter.hpp"
#include "painter/bullet_painter.hpp"
#include "painter/map_painter.hpp"
#include "painter/state_painter.hpp"

/**
 * 坦克游戏逻辑处理
 * 
 * 具体来讲, 接收外部的调用, 更新元素的状态.
 * 注意:
 *  - 只负责元素管理, 不负责元素创建.
 *  - 绘制行为仅绘制了元素本身到对应元素的位图空间
*/
class TankEngine
{
private:
    std::vector<int>    mCmds;          // 存放每个周期的命令
    std::list<Tank*>    mTanks;         // 坦克列表
    std::list<Tank*>    mTmpTanks;      // 临时坦克列表
    std::list<Bullet*>  mBullets;       // 子弹列表
    std::list<Bullet*>  mTmpBullets;    // 临时子弹列表
    Map *mMap;
    State *mState;
    TankPainter     tankPainter;
    BulletPainter   bulletPainter;
    MapPainter      mapPainter;
    StatePainter    statePainter;
    Generator generator;
    Detector *detector;
    
    void updateTank();
    int getTankAction(Tank* tank);
    bool moveTank(Tank *tank, int action);
    void drawTank(Tank *tank);
    void fireBullet(Tank *tank, int action);
    
    void updateBullet();
    void moveBullet(Bullet *bullet);
    void drawBullet(Bullet* bullet);

    void updateMap();
    void updateState();
    void handleCollision();
    void tickMoveElement();
public:
    TankEngine();
    ~TankEngine();
    /// @brief 每一帧刷新
    void refresh();
    /// @brief 处理输入命令
    /// @param cmd 0~7表示行为（包括方向, 开火等）, 8~15位表示元素标志（包括坦克标识）
    /// @return 是否退出游戏
    bool handle(int cmd);
    /// @brief 获取绘制元素
    /// @return 获取绘制元素
    std::list<Element*> getElements();

    /// 以下代码主要用来测试
    void addTank(Tank *tank);
    void addBullet(Bullet *bullet);
    void bindMap(Map *map);
    void bindState(State *state);
    std::list<Tank*>    getTanks();
    std::list<Bullet*>  getBullets();
    std::vector<int>    getCmd();
};

#endif // _ENGINE_HPP_
