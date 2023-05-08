#include <gtest/gtest.h>

#include "engine.hpp"
#include "element/tank.hpp"
#include "painter/tank_painter.hpp"

TEST(TankTest, SetTank) {
    Tank t(RIGHT, 4);
    EXPECT_EQ(RIGHT, t.getDirection());
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
    engine.addTank(t);
    EXPECT_EQ(1, engine.getTanks().size());

    engine.handle(PLAYER_ID_1 | DOWN);
    EXPECT_EQ(1, engine.getCmd().size());

    engine.refresh();
    EXPECT_EQ(0, engine.getCmd().size());

    Position pos = t->getPosition();
    EXPECT_EQ(Position(0, 1), pos);
    EXPECT_EQ(9, t->getTimer());


    int row, col;
    int **bitmap = t->getBitmap(row, col);
    EXPECT_EQ(bitmap[2][1], '*');

    engine.handle(PLAYER_ID_1 | DOWN);
    engine.refresh();
    EXPECT_EQ(8, t->getTimer());
    EXPECT_EQ(1, engine.getCmd().size());

    for (int i = 0; i < 9; i++)
    {
        EXPECT_EQ(1, engine.getCmd().size());
        EXPECT_EQ(Position(0, 1), t->getPosition());
        engine.refresh();
    }
    EXPECT_EQ(0, engine.getCmd().size());

    EXPECT_EQ(9, t->getTimer());
    EXPECT_EQ(Position(0, 2), t->getPosition());

}