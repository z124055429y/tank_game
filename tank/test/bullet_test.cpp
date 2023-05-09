#include <gtest/gtest.h>

#include "engine.hpp"
#include "element/bullet.hpp"

TEST(BulletTest, SetBullet) {
    Bullet *b = new Bullet(3, 3, RIGHT);
    EXPECT_EQ(Position(3, 3), b->getPosition());
    EXPECT_EQ(RIGHT, b->getStatus() & MASK_DIRECTION);
    delete b;
}

TEST(BulletTest, UpdateBullet) {
    Bullet b(3, 3, DOWN);
    TankEngine engine;
    engine.addBullet(&b);

    engine.refresh();
    EXPECT_EQ(Position(3, 4), b.getPosition());
}
