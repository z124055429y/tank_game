#include <gtest/gtest.h>

#include "base/element.hpp"

TEST(ElementTest, InitElement) {
  Element *e = new Element(1, 2, 3, 4, UP);
  Position pos = e->getPosition();
  Size size = e->getSize();
  int dir = e->getDirection();
  
  EXPECT_EQ(Position(1, 2), pos);
  EXPECT_EQ(Size(3, 4), size);
  EXPECT_EQ(UP, dir);
}