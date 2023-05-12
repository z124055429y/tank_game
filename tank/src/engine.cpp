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
    switch (cmd & MASK_PUSH_SCENE)
    {
    case PUSH_SCENE_GAME: pushScene = new GameScene(); break;
    }
    if (pushScene != nullptr) {
        pushScene->init();
        mScene.push_back(pushScene);
    }

    return mScene.size() == 0;
}

void TankEngine::refresh() {
    Scene *scene = mScene.back();
    scene->refresh();
}

std::list<Element*> TankEngine::getElements() {
    Scene *scene = mScene.back();
    return scene->getElements();
}