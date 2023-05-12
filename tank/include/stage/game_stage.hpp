#if !defined(_GAME_STAGE_HPP_)
#define _GAME_STAGE_HPP_

#include <list>
#include <vector>
#include <string>

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
#include "io/io.hpp"

class GameStage
{
friend class IO;
private:
    std::vector<int>    mCmds;          // 存放每个周期的命令
    std::list<Tank*>    mTanks;         // 坦克列表
    std::list<Tank*>    mTmpTanks;      // 临时坦克列表
    std::list<Bullet*>  mBullets;       // 子弹列表
    std::list<Bullet*>  mTmpBullets;    // 临时子弹列表
    Map* mMap;
    State* mState;
    
    TankPainter     tankPainter;
    BulletPainter   bulletPainter;
    MapPainter      mapPainter;
    StatePainter    statePainter;
    Generator generator;
    Detector *mDetector;
    bool isFreeze;

    
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
    GameStage(/* args */);
    ~GameStage();
    void init();
    void load(std::string path);
    void save(std::string path);

    /// @brief 每一帧刷新
    void refresh();
    /// @brief 处理输入命令
    /// @param cmd 0~7表示行为（包括方向, 开火等）, 8~15位表示元素标志（包括坦克标识）
    /// @return 是否退出游戏
    bool handle(int cmd);
    /// @brief 获取绘制元素
    /// @return 获取绘制元素
    std::list<Element*> getElements();
    /// 当前关卡是否结束
    bool isEnd() { return mTanks.size() == 1; }
    /// @brief 是否暂停
    void freeze() { isFreeze = true; }

    void addTank(Tank *tank);
    void addBullet(Bullet *bullet);
    void bindMap(Map *map);
    void bindDetector(Detector *detector);
    void bindState(State *state);
    
    /// 以下代码主要用来测试
    std::list<Tank*>    getTanks() { return mTanks; }
    std::list<Bullet*>  getBullets() { return mBullets; }
    std::vector<int>    getCmd() { return mCmds; };
    Map*                getMap() { return mMap; };
};



#endif // _GAME_STAGE_HP
