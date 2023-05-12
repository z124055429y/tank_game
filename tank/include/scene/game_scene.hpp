#if !defined(_GAME_SCENE_)
#define _GAME_SCENE_

#include "base/scene.hpp"
#include "handler/game_handler.hpp"
#include "stage/game_stage.hpp"

class GameScene: public Scene
{
private:
    GameStage *stage;
public:
    GameScene();
    ~GameScene();
    void init();
    bool input(int ch);
    void refresh();
    std::list<Element*> getElements();
};


#endif // _GAME_SCENE_
