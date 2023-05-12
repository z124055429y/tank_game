#include <list>
#include "scene/start_scene.hpp"

StartScene::StartScene(/* args */)
{
}

StartScene::~StartScene()
{
}

void StartScene::init() {
    std::list<std::string> items;
    items.push_back("Welcome to Tank Game");
    items.push_back("enter [s] to start game");
    items.push_back("enter [q] to quit game");
    items.push_back("enter [r] to restore game");

    mMenu = new Menu(5, 5, items);
}

int StartScene::input(int ch) {
    if (ch == 's') {
        return PUSH_SCENE_GAME;
    } else if (ch = 'r') {
        return PUSH_RESTORE_GAME;
    }
    return false;
}

void StartScene::refresh() {
    menuPainter.draw(mMenu);
}

std::list<Element*> StartScene::getElements() {
    std::list<Element*> l;
    l.push_back(mMenu);
    return l;
}