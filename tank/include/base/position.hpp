#if !defined(_POSITION_HPP_)
#define _POSITION_HPP_

#include <iostream>

/**
 * 位置信息
*/
class Position
{
friend std::ostream& operator<<(std::ostream &o, const Position &pos) {
    o << "Position(" << pos.mX << ", " << pos.mY << ")";
    return o;
}
private:
    /// @brief x坐标
    int mX;
    /// @brief y坐标
    int mY;
public:
    Position():Position(0, 0) {}
    Position(int x, int y): mX(x), mY(y) {}
    Position(const Position &other) { set(other.mX, other.mY); }
    int getX() { return mX; }
    int getY() { return mY; }
    void set(int x, int y) { mX = x, mY = y;}
    bool operator==(const Position& other) const { return mX == other.mX && mY == other.mY; }
};

#endif // _POSITION_HPP_
