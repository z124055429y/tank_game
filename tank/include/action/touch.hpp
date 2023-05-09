#if !defined(_TOUCH_HPP_)
#define _TOUCH_HPP_

#include "base/element.hpp"

/**
 * 可接触
*/
class Touch
{
public:
    /// @brief 当前接触元素在origin元素的什么方位
    /// @param origin 参照元素
    /// @return 返回方位位图
    virtual int touch(Element *origin) = 0;
};


#endif // _TOUCH_HPP_
