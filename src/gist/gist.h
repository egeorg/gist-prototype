#pragma once

#include <vector>

#include "gist/predicate.h"
#include "gist/inner_entry.h"
#include "gist/leaf_entry.h"
//#include "gist/node.h"

template <typename P>
class Gist {
private:
    int max_fanout;
    int min_fanout;
    InnerEntry<P> *root;

    InnerEntry<P> chooseSubtree(LeafEntry<P> const &E);
    void split(InnerEntry<P> &L, Entry<P> const &E);
    void adjustKeys(InnerEntry<P> &L);
public:
    Gist(int max_fanout, int min_fanout);
    virtual ~Gist();

    std::vector<LeafEntry<P> *> search(const P &p) const;
    void insert(const LeafEntry<P> &E);
    void deleteEntry(const Entry<P> &e);
};

// this is not good..
#include "gist/gist.cxx"