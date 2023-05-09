#include <gtest/gtest.h>

#include <vector>

TEST(Test, Test) {
    std::vector<int> test(10, 0);
    EXPECT_EQ(10, test.size());
}