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
#include "scene/game_scene.hpp"

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
    std::list<Scene*> mScene;
public:
    TankEngine();
    ~TankEngine();
    /// @brief 每一帧刷新
    void refresh();
    /// @brief 获取绘制元素
    /// @return 获取绘制元素
    std::list<Element*> getElements();
    /// @brief 输入
    /// @param op 输入 
    /// @return 是否退出
    bool input(int op);
    /// @brief 初始化
    void init();
    /// @brief 销毁
    void destroy() {}

};

#endif // _ENGINE_HPP_
