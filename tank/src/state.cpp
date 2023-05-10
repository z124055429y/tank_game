#include "element/state.hpp"

State::State(int x, int y, int rows, int cols, int playerNum): Element(x, y, rows, cols), mScore(playerNum, 0) {}
State::~State() {}

void State::addScore(int index, int score) {
    if (index >= mScore.size() || index < 0) return;
    mScore[index] += score;
}
