#if !defined(_TANK_HPP_)
#define _TANK_HPP_

#include "base/element.hpp"
#include "base/painter.hpp"
#include "action/move.hpp"
#include "action/touch.hpp"

/**
 * 坦克类
 * 
 * 速度: 10帧
*/
class Tank: public Element, public Move, public Touch
{
private:
    Timer mFireTimer;
    int mBulletDamage;  // 子弹伤害
    /// @brief 血量
    int mHp;
public:
    Tank(STATUS status, int hp);
    ~Tank();
    /// @brief 是否死亡
    bool isDead();
    /// @brief 添加血量, 注意越界处理
    void addHp(int plusHp);
    /// @brief 减少血量, 注意越界处理
    void minusHp(int minusHp);
    void move(int dir);
    void tick(bool manual);
    int getHp() { return mHp; }
    bool isFireReady() { return mFireTimer.isReady(); }
    void fireReset() { mFireTimer.reset(); }
    int touch(Element *origin);
};

#endif // _TANK_HPP_
