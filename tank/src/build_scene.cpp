#include "scene/build_scene.hpp"

BuildScene::BuildScene(std::string path): pStage(nullptr), mPath(path)
{
    pStage = new GameStage();
    pStage->freeze();
}

BuildScene::~BuildScene()
{
    delete pStage;
}

void BuildScene::init() {
    Map *map = new Map(20, 40);
    Tank *tank1 = new Tank(PLAYER_ID_1|DOWN, 3);
    tank1->setPosition({1, 1});
    Tank *tank2 = new Tank(ENERMY_ID_1|DOWN, 3);
    tank2->setPosition({36, 1});
    pStage->addTank(tank1);
    pStage->addTank(tank2);
    pStage->bindMap(map);

    std::list<std::string> items;
    items.push_back("[Y] Grass");
    items.push_back("[#] Iron Wall");
    items.push_back("[^] Mud Wall");
    items.push_back("[~] River");
    items.push_back("[S] StartGame");
    pMenu = new Menu(90, 5, items);
}

int BuildScene::input(int ch, int x, int y) {
    switch (ch)
    {
    case '^': mSelectLand = LAND_MUD_WALL; break;
    case '#': mSelectLand = LAND_IRON_WALL; break;
    case '~': mSelectLand = LAND_RIVER; break;
    case 'Y': mSelectLand = LAND_GRASS; break;
    case 'S': pStage->save(mPath); return POP_SCENE_BUILD|PUSH_SCENE_GAME;
    }
    int mask = LAND_MUD_WALL | LAND_IRON_WALL | LAND_RIVER | LAND_GRASS;
    Map *map = pStage->getMap();
    Size size = map->getSize();
    Position pos = map->getPosition();
    bool rowIn = y > pos.getY() && y < (pos.getY() + size.getRows() - 2);
    bool colIn = x > pos.getX() && x < (pos.getX() + size.getCols() - 2);
    if ((mask & mSelectLand) != 0 && (rowIn && colIn)) {
        (*map)[y - pos.getY()][x - pos.getX()] = mSelectLand;
    }
    return 0;
}

void BuildScene::refresh() {
    pStage->refresh();
    menuPainter.draw(pMenu);
}

std::list<Element*> BuildScene::getElements() {
    std::list<Element*> elems = pStage->getElements();
    elems.push_back(pMenu);
    return elems;
}