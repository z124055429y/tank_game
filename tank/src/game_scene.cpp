#include "scene/game_scene.hpp"

GameScene::GameScene() {
    stage = new GameStage();
}

GameScene::~GameScene() {
    delete stage;
}

std::list<Element*> GameScene::getElements() {
    return stage->getElements();
}

void GameScene::init() {
    stage->init();
    // stage->load("/Users/zhangyue/Project/c_languague/tank1/tank/res/tmp.txt");
}
    
bool GameScene::input(int ch) {
    int cmd = GameHandler::generateCommand(ch);
    if (cmd == 0) return false;
    return stage->handle(cmd);
}

void GameScene::refresh() {
    stage->refresh();
}