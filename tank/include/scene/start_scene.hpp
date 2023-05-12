#if !defined(_START_SCENE_HPP_)
#define _START_SCENE_HPP_

#include <list>

#include "base/element.hpp"
#include "base/scene.hpp"
#include "element/menu.hpp"
#include "painter/menu_painter.hpp"

class StartScene: public Scene
{
private:
    Menu *mMenu;
    MenuPainter menuPainter;
public:
    StartScene(/* args */);
    ~StartScene();

    void init();
    int input(int ch, int x, int y);
    void refresh();
    bool isEnd() { return false; }
    std::list<Element*> getElements();
};



#endif // _START_SCENE_HPP_
