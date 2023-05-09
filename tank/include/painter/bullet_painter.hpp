#if !defined(_BULLET_PAINTER_HPP_)
#define _BULLET_PAINTER_HPP_

#include "element/bullet.hpp"

class BulletPainter
{
public:
    void draw(Bullet *bullet) {
        if (bullet == nullptr) return;
        Bullet &b = *bullet;

        int rows, cols;
        int **bitmap = bullet->getBitmap(rows, cols);
        bitmap[0][0] = '+';
    }
};

#endif // _BULLET_PAINTER_HPP_
