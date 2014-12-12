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

    //InnerEntry<P> chooseSubtree(LeafEntry<P> const &E);
    //void split(Entry<P> E, std::stack<InnerEntry<P>*> path);
    //void adjustKeys(InnerEntry<P> &L);
public:
    Gist(int max_fanout, int min_fanout);
    virtual ~Gist();

    std::vector<LeafEntry<P> *> search(const P &p) const;

    void insert(LeafEntry<P> E);

    void deleteEntry(const LeafEntry<P> &e);
};

// this is not good..
#include "gist/gist.cxx"