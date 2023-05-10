#include <gtest/gtest.h>

#include "painter/map_painter.hpp"

TEST(MapTest, SetMap) {
    Map map(20,40);
    EXPECT_EQ(LAND_BORDER, map[0][0] & MASK_LAND);
    EXPECT_EQ(LAND_BORDER, map[19][0] & MASK_LAND);
    EXPECT_EQ(LAND_BORDER, map[0][39] & MASK_LAND);
    EXPECT_EQ(LAND_BORDER, map[19][39] & MASK_LAND);
}

TEST(MapTest, DrawMap) {
    Map map(20, 40);
    MapPainter painter;
    int rows, cols;
    int **b = map.getBitmap(rows, cols);

    // 绘制
    painter.draw(&map);
    EXPECT_EQ('#', b[0][0]);
    EXPECT_EQ('#', b[19][0]);
    EXPECT_EQ('#', b[0][39]);
    EXPECT_EQ('#', b[19][39]);
}