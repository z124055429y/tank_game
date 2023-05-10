#include <gtest/gtest.h>

#include "engine.hpp"

TEST(StateTest, DrawState) {
    TankEngine engine;
    State *state = new State(0, 0, 3, 20, 1);
    engine.bindState(state);

    engine.refresh();
    int rows, cols;
    int **bitmap = state->getBitmap(rows, cols);
    EXPECT_EQ('P', bitmap[0][0]);

    delete state;

}