#include <gtest/gtest.h>

#include "engine.hpp"
#include "element/tank.hpp"
#include "painter/tank_painter.hpp"

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
    TankEngine engine;

    // 初始化timer为0
    EXPECT_EQ(0, t->getTimer());
    
    // 添加坦克
    engine.addTank(t);
    EXPECT_EQ(1, engine.getTanks().size());

    // 玩家1向下
    engine.handle(PLAYER_ID_1 | DOWN);
    EXPECT_EQ(PLAYER_ID_1 | DOWN, engine.getCmd()[0]);

    // 刷新一帧
    engine.refresh();
    EXPECT_EQ(PLAYER_ID_1, engine.getCmd()[0]);

    // 检查位置
    Position pos = t->getPosition();
    EXPECT_EQ(DOWN, t->getStatus() & MASK_DIRECTION);
    EXPECT_EQ(Position(0, 1), pos);
    EXPECT_EQ(2, t->getTimer());

}

TEST(TankTest, Fire) {
    Tank *t = new Tank(PLAYER_ID_1 | RIGHT, 4);
    t->setPosition({3, 3});
    TankEngine engine;
    engine.addTank(t);

    engine.handle(PLAYER_ID_1 | FIRE);

    engine.refresh();
    Bullet *b = engine.getBullets().front();
    EXPECT_EQ(Position(6, 4), b->getPosition());

    delete t;
}