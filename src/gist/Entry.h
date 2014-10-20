#pragma once

#include "gist/predicate.h"

template <typename P>
class Entry {
private:
    P predicate;

public:
    void setPredicate(P const &predicate) {
        Entry::predicate = predicate;
    }

    P getPredicate() const {
        return predicate;
    }
};