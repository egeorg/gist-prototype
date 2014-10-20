#pragma once

#include <vector>

#include "gist/predicate.h"
#include "gist/entry.h"
#include "gist/node.h"

// TODO: InnerEntry, LeafEntry
// Разделение на Node, Entry
// Node хранит вектор Entry
// Параметризовать Gist<ConcretePredicate> предикатом

template <typename P>
class Gist {
private:
    int upperBound;
    int lowerBound;
    Node<P> *root;

public:
    Gist(int upperBound, int lowerBound);
    virtual ~Gist();

    std::vector<Entry<P> *> search(const P &p) const;
    void insert(const Entry<P> &e);
    void deleteEntry(const Entry<P> &e);
};

// this is not good..
#include "gist/gist.cxx"