#include <ctime>
#include <cstdlib>

#include "engine.hpp"

TankEngine::TankEngine() {
    scene = new GameScene();
}
TankEngine::~TankEngine() {
    delete scene;
}

void TankEngine::init() {
    scene->init();
}

bool TankEngine::input(int op) {
    return scene->input(op);
}

void TankEngine::refresh() {
    scene->refresh();
}

std::list<Element*> TankEngine::getElements() {
    return scene->getElements();
}