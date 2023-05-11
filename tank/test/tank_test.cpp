#include <gtest/gtest.h>

#include "scene/game_scene.hpp"

TEST(TankTest, SetTank) {
    Tank t(RIGHT, 4);
    EXPECT_EQ(RIGHT, t.getStatus());
    EXPECT_EQ(false, t.isDead());

    t.minusHp(4);
    EXPECT_EQ(true, t.isDead());
}

TEST(TankTest, DrawTank) {
    Tank t(UP,4);
    TankPainter p('*');
    int row, col;
    int **bitmap = t.getBitmap(row, col);
    
    // 第一次绘制
    p.draw(&t);
    EXPECT_EQ(bitmap[0][1], '*');

    // 更改方向绘制
    t.setDirection(RIGHT);
    p.draw(&t);
    EXPECT_EQ(bitmap[1][2], '*');
}

TEST(TankTest, MoveTank) {
    Tank *t = new Tank(PLAYER_ID_1 | UP, 4);
    GameStage stage;

    // 初始化timer为0
    EXPECT_EQ(0, t->getTimer());
    
    // 添加坦克
    stage.addTank(t);
    EXPECT_EQ(1, stage.getTanks().size());

    // 玩家1向下
    stage.handle(PLAYER_ID_1 | DOWN);
    EXPECT_EQ(PLAYER_ID_1 | DOWN, stage.getCmd()[0]);

    // 刷新一帧
    stage.refresh();
    EXPECT_EQ(PLAYER_ID_1, stage.getCmd()[0]);

    // 检查位置
    Position pos = t->getPosition();
    EXPECT_EQ(DOWN, t->getStatus() & MASK_DIRECTION);
    EXPECT_EQ(Position(0, 1), pos);

}

TEST(TankTest, Fire) {
    Tank *t = new Tank(PLAYER_ID_1 | RIGHT, 4);
    t->setPosition({3, 3});
    GameStage stage;
    stage.addTank(t);

    stage.handle(PLAYER_ID_1 | FIRE);

    stage.refresh();
    Bullet *b = stage.getBullets().front();
    EXPECT_EQ(Position(6, 4), b->getPosition());

    delete t;
}

TEST(TankTest, SetEnermyTank) {
    Tank *t = new Tank(ENERMY_ID_1 | RIGHT, 4);
    t->setPosition({3, 3});
    GameStage stage;
    stage.addTank(t);
    for (size_t i = 0; i < 1; i++)
    {
        stage.refresh();
    }

    delete t;

}