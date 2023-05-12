#if !defined(_GAME_SCENE_)
#define _GAME_SCENE_

#include "base/scene.hpp"
#include "handler/game_handler.hpp"
#include "stage/game_stage.hpp"
#include "element/state.hpp"

class GameScene: public Scene
{
private:
    State *mState;
    std::vector<std::string> mStagePaths;
    GameStage *pStage;
    int curIndex = 0;
public:
    GameScene();
    GameScene(std::vector<std::string> paths);
    ~GameScene();
    void init();
    int input(int ch, int x, int y);
    void refresh();
    bool isEnd() { return curIndex >= mStagePaths.size() && pStage != nullptr && pStage->isEnd(); }
    std::list<Element*> getElements();
};


#endif // _GAME_SCENE_
