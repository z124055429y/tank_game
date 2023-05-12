#include <gtest/gtest.h>

#include "stage/game_stage.hpp"

TEST(DetectTest, CheckTouch) {
    GameStage stage;
    Tank *tank = new Tank(PLAYER_ID_1|UP, 1);
    Map *map = new Map(40,20);
    Detector *detector = new Detector({40,20});
    tank->setPosition({2, 1});
    stage.addTank(tank);
    stage.bindMap(map);
    stage.bindDetector(detector);
    
    EXPECT_EQ(Position(2, 1), tank->getPosition());

    stage.handle(PLAYER_ID_1|LEFT);
    stage.refresh();

    EXPECT_EQ(Position(1, 1), tank->getPosition());
}

TEST(DetectTest, CheckBulletMapCollision) {
    GameStage stage;
    Tank *tank = new Tank(PLAYER_ID_1|LEFT, 1);
    tank->setPosition({2, 1});
    Map *map = new Map(40,20);
    Detector *detector = new Detector({40,20});
    stage.addTank(tank);
    stage.bindMap(map);
    stage.bindDetector(detector);

    stage.handle(PLAYER_ID_1|FIRE);
    stage.refresh();

    EXPECT_EQ(1, stage.getBullets().size());
    stage.refresh();
    stage.refresh();
    stage.refresh();
    stage.refresh();
    EXPECT_EQ(0, stage.getBullets().size());
}

TEST(DetectTest, CheckBulletBulletCollision) {
    GameStage stage;
    Map *map = new Map(40,20);
    Detector *detector = new Detector({40,20});
    stage.bindMap(map);
    stage.bindDetector(detector);

    // 同一点的碰撞
    Bullet *bullet1 = new Bullet(3, 2, DOWN);
    Bullet *bullet2 = new Bullet(2, 3, RIGHT);
    stage.addBullet(bullet1);
    stage.addBullet(bullet2);

    EXPECT_EQ(2, stage.getBullets().size());
    stage.refresh();
    stage.refresh();
    stage.refresh();
    stage.refresh();
    EXPECT_EQ(0, stage.getBullets().size());

    // 穿模碰撞
    Bullet *bullet3 = new Bullet(6, 6, DOWN);
    Bullet *bullet4 = new Bullet(6, 7, UP);
    stage.addBullet(bullet3);
    stage.addBullet(bullet4);
    EXPECT_EQ(2, stage.getBullets().size());
    stage.refresh();
    stage.refresh();
    stage.refresh();
    stage.refresh();
    EXPECT_EQ(0, stage.getBullets().size());

    // ps: 子弹销毁已经在stage中处理过了
}

TEST(DetectTest, CheckTankBulletCollision) {
    GameStage stage;
    Map *map = new Map(40,20);
    Detector *detector = new Detector({40,20});
    Tank *tank = new Tank(PLAYER_ID_1|DOWN, 3);
    Bullet *bullet = new Bullet(3, 2, DOWN);
    tank->setPosition({3, 3});
    stage.bindMap(map);
    stage.bindDetector(detector);
    stage.addTank(tank);
    stage.addBullet(bullet);

    stage.refresh();
    stage.refresh();
    stage.refresh();
    stage.refresh();
    EXPECT_EQ(2, tank->getHp());

}