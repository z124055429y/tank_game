#include <gtest/gtest.h>

#include "stage/game_stage.hpp"

TEST(BulletTest, SetBullet) {
    Bullet *b = new Bullet(3, 3, RIGHT);
    EXPECT_EQ(Position(3, 3), b->getPosition());
    EXPECT_EQ(RIGHT, b->getStatus() & MASK_DIRECTION);
}

TEST(BulletTest, UpdateBullet) {
    Bullet *b = new Bullet(3, 3, DOWN);
    GameStage stage;
    stage.addBullet(b);

    stage.refresh();
    stage.refresh();
    stage.refresh();
    EXPECT_EQ(Position(3, 3), b->getPosition());

    stage.refresh();
    EXPECT_EQ(Position(3, 4), b->getPosition());
}
