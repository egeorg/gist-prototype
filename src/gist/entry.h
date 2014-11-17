#pragma once

#include "gist/predicate.h"
#include "gist/predicate_holder.h"

template <typename P>
class Entry : public PredicateHolder {
private:
    P predicate;
public:
    void setPredicate(P const &predicate) {
        this->predicate = predicate;
    }

    virtual std::vector<Entry<P> *> getChildren() = 0;

    P getPredicate() const {
        return predicate;
    }
};