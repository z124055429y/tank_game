#if !defined(_BUILD_SCENE_HPP_)
#define _BUILD_SCENE_HPP_

#include "base/scene.hpp"
#include "element/menu.hpp"
#include "element/map.hpp"
#include "element/tank.hpp"
#include "stage/game_stage.hpp"

class BuildScene: public Scene
{
private:
    Map* map;
    GameStage* pStage;
public:
    BuildScene(/* args */);
    ~BuildScene();
    
    void init();
    int input(int ch);
    void refresh();
    bool isEnd() { return false; }
    std::list<Element*> getElements();
};



#endif // _BUILD_SCENE_HPP_
