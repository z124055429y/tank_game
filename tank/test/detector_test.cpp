#include <gtest/gtest.h>

#include "engine.hpp"

TEST(DetectTest, CheckTouch) {
    TankEngine engine;
    Tank *tank = new Tank(PLAYER_ID_1|UP, 1);
    tank->setPosition({2, 1});
    Map *map = new Map(40,20);
    engine.addTank(tank);
    engine.bindMap(map);
    
    EXPECT_EQ(Position(2, 1), tank->getPosition());

    engine.handle(PLAYER_ID_1|LEFT);
    engine.refresh();

    EXPECT_EQ(Position(1, 1), tank->getPosition());

    delete map;
    delete tank;
}

TEST(DetectTest, CheckCollision) {
    TankEngine engine;
    Tank *tank = new Tank(PLAYER_ID_1|LEFT, 1);
    tank->setPosition({2, 1});
    Map *map = new Map(40,20);
    engine.addTank(tank);
    engine.bindMap(map);

    engine.handle(PLAYER_ID_1|FIRE);
    engine.refresh();

    EXPECT_EQ(1, engine.getBullets().size());

    engine.refresh();
    engine.refresh();
    engine.refresh();
    engine.refresh();
    engine.refresh();
    engine.refresh();
    engine.refresh();

    EXPECT_EQ(0, engine.getBullets().size());
}