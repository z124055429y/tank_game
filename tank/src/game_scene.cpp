#include "scene/game_scene.hpp"

GameScene::GameScene(): pStage(nullptr) {
}

GameScene::GameScene(std::vector<std::string> paths): pStage(nullptr), mStagePaths(paths) {
}

GameScene::~GameScene() {
    delete pStage;
}

std::list<Element*> GameScene::getElements() {
    if (pStage == nullptr) return {};
    return pStage->getElements();
}

void GameScene::init() {
    State *state = new State(90, 4, 3, 20, 1);
    mState = state;
}
    
int GameScene::input(int ch, int x, int y) {
    if (ch == 'S') {
        pStage->save("/Users/zhangyue/Project/c_languague/tank1/tank/res/tmp.txt");
        return POP_SCENE_GAME;
    }
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
        pStage->bindState(mState);
        curIndex++;
    }
}