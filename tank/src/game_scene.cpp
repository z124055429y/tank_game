#include "scene/game_scene.hpp"

std::list<Element*> GameScene::getElements() {
    return stage.getElements();
}

void GameScene::init() {
    stage.init();
}
    
bool GameScene::input(int ch) {
    int cmd = GameHandler::generateCommand(ch);
    if (cmd == 0) return false;
    return stage.handle(cmd);
}

void GameScene::refresh() {
    stage.refresh();
}