#include <gtest/gtest.h>
#include "gist/gist.h"

TEST(UnitTests, SampleTest) {
    EXPECT_EQ(1 + 1, 2);
}

TEST(UnitTests, CreatingGistInstance) {
	Gist<int> g(0, 0);
}
