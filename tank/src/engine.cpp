#include <ctime>
#include <cstdlib>

#include "engine.hpp"
#include "scene/start_scene.hpp"

TankEngine::TankEngine() {
    // scene = new GameScene();
    StartScene *scene = new StartScene();
    mScene.push_back(scene);
}
TankEngine::~TankEngine() {
    if (mScene.size() != 0) {
        for (auto &&scene : mScene)
        {
            delete scene;
        }
    }
}

void TankEngine::init() {
    Scene *scene = mScene.back();
    scene->init();
}

bool TankEngine::input(int op) {
    Scene *scene = mScene.back();
    int cmd = scene->input(op);
    Scene *pushScene = nullptr;
    
    std::vector<std::string> paths;
    switch (cmd & MASK_PUSH_SCENE)
    {
    case PUSH_SCENE_GAME:
        paths.push_back("/Users/zhangyue/Project/c_languague/tank1/tank/res/stage/stage1.txt");
        paths.push_back("/Users/zhangyue/Project/c_languague/tank1/tank/res/stage/stage2.txt");
        pushScene = new GameScene(paths);
        pushScene->init();
        break;
    case PUSH_RESTORE_GAME:
        paths.push_back("/Users/zhangyue/Project/c_languague/tank1/tank/res/tmp.txt");
        paths.push_back("/Users/zhangyue/Project/c_languague/tank1/tank/res/stage/stage1.txt");
        paths.push_back("/Users/zhangyue/Project/c_languague/tank1/tank/res/stage/stage2.txt");
        pushScene = new GameScene(paths);
        pushScene->init();
        break;
    }
    switch (cmd & MASK_POP_SCENE)
    {
    case POP_SCENE_GAME:
        mScene.pop_back();
        break;
    }
    if (pushScene != nullptr) {
        mScene.push_back(pushScene);
    }

    return mScene.size() == 0;
}

void TankEngine::refresh() {
    Scene *scene = mScene.back();
    if (scene->isEnd()) {
        mScene.pop_back();
        scene = mScene.back();
    }
    scene->refresh();
}

std::list<Element*> TankEngine::getElements() {
    Scene *scene = mScene.back();
    return scene->getElements();
}