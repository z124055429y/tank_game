#include <cstdio>

#include "io/io.hpp"
#include "stage/game_stage.hpp"

void setElement(Element *e, int x, int y, STATUS status);

void IO::load(std::string path, GameStage *stage) {
    FILE *f = fopen(path.c_str(), "r");
    char buf[BUFSIZ];
    int x, y, rows, cols;
    STATUS status;
    int ret = 0;
    while ((ret = fscanf(f, "%s %d,%d,%d,%d,%d", buf, &x, &y, &rows, &cols, &status)) > 0) {
        // printf("%s, %d, %d, %d, %d, %d\n");
        if (strcmp(buf, "map") == 0) {
            loadMap(f, stage, x, y, rows, cols, status);
        } else if (strcmp(buf, "tank") == 0) {
            loadTank(f, stage, x, y, rows, cols, status);
        }
    }
    fclose(f);
}

void IO::save(std::string path, GameStage *stage) {
    FILE *f = fopen(path.c_str(), "w");
    Map *map = stage->mMap;
    saveMap(f, map);
    auto tanks = stage->mTanks;
    for (auto &&tank : tanks)
    {
        saveTank(f, tank);
    }
    fclose(f);
}

void IO::loadMap(FILE *f, GameStage *stage, int x, int y, int rows, int cols, STATUS status) {
    Map *map = new Map(rows, cols);
    Detector *detector = new Detector({rows, cols});
    setElement(map, x, y, status);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fscanf(f, "%d", &((*map)[i][j]));
        }
        
    }

    stage->bindMap(map);
    stage->bindDetector(detector);
}

void IO::saveMap(FILE *f, Map *map) {
    Size mapSize = map->getSize();
    Position mapPos = map->getPosition();
    STATUS status = map->getStatus();
    fprintf(f, "map %d,%d,%d,%d,%d\n", mapPos.getX(), mapPos.getY(), mapSize.getRows(), mapSize.getCols(), status);
    for (int i = 0; i < mapSize.getRows(); i++)
    {
        for (int j = 0; j < mapSize.getCols(); j++)
        {
            if (j != 0) fprintf(f, " ");
            fprintf(f, "%2d", (*map)[i][j]);
        }
        fprintf(f, "\n");
    }
}

void IO::saveTank(FILE *f, Tank *tank) {
    Size mapSize = tank->getSize();
    Position mapPos = tank->getPosition();
    STATUS status = tank->getStatus();
    fprintf(f, "tank %d,%d,%d,%d,%d\n", mapPos.getX(), mapPos.getY(), mapSize.getRows(), mapSize.getCols(), status);
    fprintf(f, "%d,%d,%d,%d\n", tank->getHp(), tank->getSpeed(), tank->getBulletDamage(), tank->getBulletSpeed());
}

void IO::loadTank(FILE *f, GameStage *stage, int x, int y, int rows, int cols, STATUS status) {
    int hp = 0, damage = 0, speed = 0, bulletSpeed =0;
    int ret = fscanf(f, "%d,%d,%d,%d", &hp, &speed, &damage, &bulletSpeed);
    Tank *tank = new Tank(status, hp, damage, speed, bulletSpeed);
    setElement(tank, x, y, status);
    tank->setPosition({x, y});
    stage->addTank(tank);
}

void setElement(Element *e, int x, int y, STATUS status) {
    e->setPosition({x, y});
    e->setDirection(status);
}