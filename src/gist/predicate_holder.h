#pragma once

//#include "gist/predicate.h"

template <typename P>
class PredicateHolder {
private:
    P* predicate;
public:
    PredicateHolder() {
    }

    PredicateHolder(P *predicate) {
        this->predicate = predicate;
    }

    P *getPredicate() const {
        return predicate;
    }
};