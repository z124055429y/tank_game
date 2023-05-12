#include "scene/build_scene.hpp"

BuildScene::BuildScene(/* args */)
{
    Map *map = new Map(20, 40);
    pStage = new GameStage();
    Tank *tank1 = new Tank(PLAYER_ID_1|DOWN, 3);
    tank1->setPosition({1, 1});
    Tank *tank2 = new Tank(PLAYER_ID_1|DOWN, 3);
    tank2->setPosition({36, 1});
    pStage->addTank(tank1);
    pStage->addTank(tank2);
}

BuildScene::~BuildScene()
{
    delete pStage;
}

void init() {
    
}

int input(int ch) {
    return 0;
}

void refresh() {

}

std::list<Element*> getElements() {
    std::list<Element*> li;
    return li;
}