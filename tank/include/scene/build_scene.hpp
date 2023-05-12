#if !defined(_BUILD_SCENE_HPP_)
#define _BUILD_SCENE_HPP_

#include <string>

#include "base/scene.hpp"
#include "element/menu.hpp"
#include "element/map.hpp"
#include "element/tank.hpp"
#include "element/menu.hpp"
#include "element/input.hpp"
#include "stage/game_stage.hpp"
#include "painter/menu_painter.hpp"
#include "painter/input_painter.hpp"

class BuildScene: public Scene
{
private:
    GameStage* pStage;
    Menu* pMenu;
    Input* pInput;
    MenuPainter menuPainter;
    InputPainter inputPainter;
    int mSelectLand;
    std::string mPath;

    void parseCommand(std::string cmd);
public:
    BuildScene(std::string path);
    ~BuildScene();
    
    void init();
    int input(int ch, int x, int y);
    void refresh();
    bool isEnd() { return false; }
    std::list<Element*> getElements();
};



#endif // _BUILD_SCENE_HPP_
