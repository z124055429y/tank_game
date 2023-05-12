#if !defined(_SCENE_HPP_)
#define _SCENE_HPP_

#include <base/element.hpp>
#include <list>

constexpr int MASK_PUSH_SCENE   = 0xff;
constexpr int PUSH_SCENE_START  = 1;
constexpr int PUSH_SCENE_GAME   = 1 << 1;
constexpr int PUSH_RESTORE_GAME = 1 << 2;
constexpr int MASK_POP_SCENE    = 0xff00;
constexpr int POP_SCENE_START   = 1 << (0 + 8);
constexpr int POP_SCENE_GAME    = 1 << (1 + 8);

/**
 * 游戏场景 每个window视为一个场景，刷新不同的元素，响应不同的按键
*/
class Scene
{
public:
    virtual ~Scene() {};
    virtual void init() = 0;
    virtual int input(int ch) = 0;
    virtual void refresh() = 0;
    virtual bool isEnd() = 0;
    virtual std::list<Element*> getElements() = 0;
};

#endif // _SCENE_HPP_
