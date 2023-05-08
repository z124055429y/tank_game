#include <gtest/gtest.h>
#include "base/position.hpp"
#include "base/size.hpp"

TEST(BaseTest, UsePosition) {
    Position *pos = new Position(4,3);
    EXPECT_EQ(4, pos->getX());
    EXPECT_EQ(3, pos->getY());
    EXPECT_EQ(Position(4, 3), *pos);

    pos->set(5, 6);
    EXPECT_EQ(Position(5, 6), *pos);
}

TEST(BaseTest, UseSize) {
    Size size(30, 40);
    EXPECT_EQ(30, size.getRows());
    EXPECT_EQ(40, size.getCols());
    EXPECT_EQ(Size(30, 40), size);

    size.set(50, 60);
    EXPECT_EQ(Size(50, 60), size);
}