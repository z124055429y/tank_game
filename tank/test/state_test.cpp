#include <gtest/gtest.h>

#include "stage/game_stage.hpp"

TEST(StateTest, DrawState) {
    GameStage stage;
    State *state = new State(0, 0, 3, 20, 1);
    stage.bindState(state);

    stage.refresh();
    int rows, cols;
    int **bitmap = state->getBitmap(rows, cols);
    EXPECT_EQ('P', bitmap[0][0]);

}