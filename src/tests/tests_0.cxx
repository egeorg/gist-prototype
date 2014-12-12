#include <gtest/gtest.h>

#include "gist/gist.h"
#include "gist/predicates/dummy_predicate.h"

TEST(UnitTests, SampleTest) {
    EXPECT_EQ(1 + 1, 2);
}

TEST(UnitTests, CreatingGistInstance) {
    Gist<DummyPredicate> g(8, 16);
}
