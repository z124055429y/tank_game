#include "element/bullet.hpp"

Bullet::Bullet(int x, int y, STATUS status): Element(x, y, 1, 1, status), Move(3, 3), mDamage(1) {}
Bullet::~Bullet() {}

void Bullet::move(int dir) {
    Move::move(this, dir);
}