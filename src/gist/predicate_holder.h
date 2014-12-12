#pragma once

//#include "gist/predicate.h"

template <typename P>
class PredicateHolder {
public:
    virtual P *getPredicate() const = 0;
};