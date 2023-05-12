#include "scene/game_scene.hpp"

GameScene::GameScene(): pStage(nullptr) {
}

GameScene::~GameScene() {
    delete pStage;
}

std::list<Element*> GameScene::getElements() {
    if (pStage == nullptr) return {};
    return pStage->getElements();
}

void GameScene::init() {
    mStagePaths.push_back("/Users/zhangyue/Project/c_languague/tank1/tank/res/stage/stage1.txt");
    mStagePaths.push_back("/Users/zhangyue/Project/c_languague/tank1/tank/res/stage/stage2.txt");
}
    
int GameScene::input(int ch) {
    int cmd = GameHandler::generateCommand(ch);
    if (cmd == 0) return false;
    return pStage->handle(cmd);
}

void GameScene::refresh() {
    if (pStage != nullptr && !pStage->isEnd()) {
        pStage->refresh();
    } else if (curIndex >= mStagePaths.size()){
        pStage->refresh();
    } else {
        if (pStage != nullptr) {
            delete pStage;
            pStage = nullptr;
        }
        pStage = new GameStage();
        pStage->load(mStagePaths[curIndex]);
        curIndex++;
    }
}