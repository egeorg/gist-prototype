#pragma once

#include "gist/predicate.h"
//#include "gist/leaf_entry.h"

template <typename P>
class Entry {
private:
    P predicate;

public:
    void setPredicate(P const &predicate) {
        Entry::predicate = predicate;
    }

    //virtual std::vector<LeafEntry<P> *> find(P const &predicate);  

    P getPredicate() const {
        return predicate;
    }
};