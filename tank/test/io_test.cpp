#include <gtest/gtest.h>

#include "stage/game_stage.hpp"

TEST(IOTest, LoadFile) {

}

TEST(IOTest, SaveMap) {
    GameStage stage;
    Map *map = new Map(20, 40);
    map->addLand(3, 3, 5, 5, LAND_GRASS);
    stage.bindMap(map);
    const char *path = "/Users/zhangyue/Project/c_languague/tank1/tank/res/tmpMap.txt";

    FILE *f = fopen(path, "w+");
    IO::saveMap(f, map);
    rewind(f);

    char buf[BUFSIZ];
    int x = 0, y = 0, rows = 0, cols = 0;
    STATUS status = NONE;

    int ret = fscanf(f, "%s %d,%d,%d,%d,%d", buf, &x, &y, &rows, &cols, &status);
    IO::loadMap(f, &stage, x, y, rows, cols, status);
    fclose(f);

    Map *tmap = stage.getMap();
    EXPECT_EQ(Position(0, 0), tmap->getPosition());
    EXPECT_EQ(Size(20, 40), tmap->getSize());
    EXPECT_EQ(LAND_GRASS, (*tmap)[3][3]);
    EXPECT_EQ(LAND_GRASS, (*tmap)[7][7]);
    EXPECT_EQ(NONE, (*tmap)[8][7]);
}

TEST(IOTest, SaveTank) {
    GameStage stage;
    Tank *tank = new Tank(PLAYER_ID_1 | UP, 3);

    const char *path = "/Users/zhangyue/Project/c_languague/tank1/tank/res/tmpTank.txt";
    FILE *f = fopen(path, "w+");
    IO::saveTank(f, tank);
    rewind(f);

    char buf[BUFSIZ];
    int x = 0, y = 0, rows = 0, cols = 0;
    STATUS status = NONE;

    int ret = fscanf(f, "%s %d,%d,%d,%d,%d", buf, &x, &y, &rows, &cols, &status);
    IO::loadTank(f, &stage, x, y, rows, cols, status);
    fclose(f);

    EXPECT_EQ(1, stage.getTanks().size());
    Tank *ttank = stage.getTanks().back();
    EXPECT_EQ(PLAYER_ID_1|UP,ttank->getStatus());
    EXPECT_EQ(3,ttank->getHp());

}