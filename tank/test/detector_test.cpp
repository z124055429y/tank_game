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

TEST(DetectTest, CheckBulletMapCollision) {
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
    EXPECT_EQ(0, engine.getBullets().size());
}

TEST(DetectTest, CheckBulletBulletCollision) {
    TankEngine engine;
    Map *map = new Map(40,20);
    engine.bindMap(map);

    // 同一点的碰撞
    Bullet *bullet1 = new Bullet(3, 2, DOWN);
    Bullet *bullet2 = new Bullet(2, 3, RIGHT);
    engine.addBullet(bullet1);
    engine.addBullet(bullet2);

    EXPECT_EQ(2, engine.getBullets().size());
    engine.refresh();
    engine.refresh();
    engine.refresh();
    engine.refresh();
    EXPECT_EQ(0, engine.getBullets().size());

    // 穿模碰撞
    Bullet *bullet3 = new Bullet(6, 6, DOWN);
    Bullet *bullet4 = new Bullet(6, 7, UP);
    engine.addBullet(bullet3);
    engine.addBullet(bullet4);
    EXPECT_EQ(2, engine.getBullets().size());
    engine.refresh();
    engine.refresh();
    engine.refresh();
    engine.refresh();
    EXPECT_EQ(0, engine.getBullets().size());

    delete map;

    // ps: 子弹销毁已经在engine中处理过了
}

TEST(DetectTest, CheckTankBulletCollision) {
    TankEngine engine;
    Map *map = new Map(40,20);
    Tank *tank = new Tank(PLAYER_ID_1|DOWN, 3);
    Bullet *bullet = new Bullet(3, 2, DOWN);
    tank->setPosition({3, 3});
    engine.bindMap(map);
    engine.addTank(tank);
    engine.addBullet(bullet);

    engine.refresh();
    engine.refresh();
    engine.refresh();
    engine.refresh();
    EXPECT_EQ(2, tank->getHp());

    delete map;

}