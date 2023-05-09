#if !defined(_BULLET_HPP)
#define _BULLET_HPP

#include "base/element.hpp"
#include "action/move.hpp"

class Bullet: public Element, public Move
{
private:
    int mDamage;
public:
    Bullet(int x, int y, STATUS status);
    ~Bullet();
    void move(int action);
};

#endif // _BULLET_HPP
