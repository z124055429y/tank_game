#include "element/bullet.hpp"

Bullet::Bullet(int x, int y, STATUS status, int damage, int speed): Element(x, y, 1, 1, status), Move(speed, speed), mDamage(damage) {}
Bullet::~Bullet() {}

void Bullet::move(int dir) {
    Move::move(this, dir);
}