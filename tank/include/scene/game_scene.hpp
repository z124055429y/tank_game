#if !defined(_GAME_SCENE_)
#define _GAME_SCENE_

#include "base/scene.hpp"
#include "handler/game_handler.hpp"
#include "stage/game_stage.hpp"

class GameScene: public Scene
{
private:
    std::vector<std::string> mStagePaths;
    GameStage *pStage;
    int curIndex = 0;
public:
    GameScene();
    ~GameScene();
    void init();
    int input(int ch);
    void refresh();
    bool isEnd() { return curIndex >= mStagePaths.size() && pStage != nullptr && pStage->isEnd(); }
    std::list<Element*> getElements();
};


#endif // _GAME_SCENE_
