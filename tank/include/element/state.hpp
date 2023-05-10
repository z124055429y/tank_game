#if !defined(_STATE_HPP_)
#define _STATE_HPP_

#include <vector>

#include "base/element.hpp"

class State: public Element
{
private:
    std::vector<int> mScore;
public:
    State(int x, int y, int rows, int cols, int playerNum);
    ~State();
    void addScore(int index, int score);
    int getScore(int index) { return (index >= mScore.size() || index < 0) ? -1 : mScore[index]; }
    std::vector<int> getScores() { return mScore; }
};

#endif // _STATE_HPP_
