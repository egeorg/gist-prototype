#include <gtest/gtest.h>

#include "gist/gist.h"
#include "gist/predicates/dummy_predicate.h"

TEST(UnitTests, SampleTest) {
    EXPECT_EQ(1 + 1, 2);
}

TEST(UnitTests, CreatingGistInstance) {
    Gist<DummyPredicate> g(8, 16);
}

TEST(UnitTests, BasicSearchingInGist) {
    Gist<DummyPredicate> g(8, 16);
    LeafEntry<DummyPredicate> data = LeafEntry<DummyPredicate>();
    g.search(*data.getPredicate());
}

TEST(UnitTests, BasicInsertingInGist) {
    Gist<DummyPredicate> g(8, 16);
    LeafEntry<DummyPredicate> data = LeafEntry<DummyPredicate>();
    g.insert(data);
}

TEST(UnitTests, InsertAndSearchExistingElement) {
    Gist<DummyPredicate> g(8, 16);
    int some = 10;
    LeafEntry<DummyPredicate> data(&some);

    g.insert(data);
    std::vector<LeafEntry<DummyPredicate> *> result = g.search(*(data.getPredicate()));
    ASSERT_EQ(result.size(), 1);
}

TEST(UnitTests, InsertAndSearchNotExistingElement) {
    Gist<DummyPredicate> g(8, 16);
    int some = 10;
    LeafEntry<DummyPredicate> data(&some);

    g.insert(data);

    int otherSome = 20;
    LeafEntry<DummyPredicate> otherData(&otherSome);

    std::vector<LeafEntry<DummyPredicate> *> result = g.search(*(otherData.getPredicate()));
    ASSERT_EQ(result.size(), 1);
}

TEST(UnitTests, InsertSeveralElements) {
    Gist<DummyPredicate> g(8, 16);
    int some = 10;
    LeafEntry<DummyPredicate> data(&some);

    g.insert(data);
    g.insert(data);
    g.insert(data);
}

TEST(UnitTests, InsertMoreThanMaxFanoutElements) {
    Gist<DummyPredicate> g(1, 2);
    int a = 1, b = 2, c = 3, d = 4;
    LeafEntry<DummyPredicate> data1(&a);
    LeafEntry<DummyPredicate> data2(&b);
    LeafEntry<DummyPredicate> data3(&c);
    LeafEntry<DummyPredicate> data4(&d);

    g.insert(data1);
    g.insert(data2);
    g.insert(data3);
    g.insert(data4);
}

