#if !defined(_ELEMENT_HPP_)
#define _ELEMENT_HPP_

#include "base/position.hpp"
#include "base/size.hpp"
#include "base/direction.hpp"

/**
 * 游戏元素
 * 
 * 包括：位置信息、大小信息、方向信息
*/
class Element
{
protected:
    /// 不同类型的元素, 对status的解读可能不同
    STATUS mStatus;
    Position mPos;
    Size mSize;
    int **pBitmap;
public:
    Element();
    Element(int rows, int cols);
    Element(int x, int y, int rows, int cols);
    Element(int x, int y, int rows, int cols, STATUS status);
    virtual ~Element();
    /// @brief 获取元素位置
    Position getPosition();
    /// @brief 设置元素大小
    void setPosition(Position pos);
    /// @brief 获取元素大小
    Size getSize();
    /// @brief 获取元素方向
    STATUS getStatus();
    /// @brief 设置元素方向
    void setDirection(STATUS status);
    /// @brief 获取位图
    /// @param rows 位图行数 
    /// @param cols 位图列数
    /// @return 返回位图指针, 可操作
    int **getBitmap(int &rows, int &cols);
};

int** allocSpace(int rows, int cols);
void freeSpace(int **space, int rows, int cols);

#endif // _ELEMENT_HPP_
