#if !defined(_SCENE_HPP_)
#define _SCENE_HPP_

#include <base/element.hpp>
#include <list>

/**
 * 游戏场景 每个window视为一个场景，刷新不同的元素，响应不同的按键
*/
class Scene
{
public:
    virtual bool input(int ch) = 0;
    virtual void refresh() = 0;
    virtual std::list<Element*> getElements() = 0;
};

#endif // _SCENE_HPP_
