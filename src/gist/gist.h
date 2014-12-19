#pragma once

#include <vector>
#include <stack>
#include <utility>

#include "gist/predicate.h"
#include "gist/inner_entry.h"
#include "gist/leaf_entry.h"
//#include "gist/node.h"

template <typename P>
class Gist {
private:
    int max_fanout;
    int min_fanout;
    int global_nsn;
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
private:
    void locateLeaf(const P &predicate, std::stack<std::pair<InnerEntry<P>*, int>> *path);

    std::vector<Entry<P>*> covariant_cast(const std::vector<PredicateHolder<P>*> &p);
};

// this is not good..
#include "gist/gist.cxx"