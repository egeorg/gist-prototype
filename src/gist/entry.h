#pragma once

#include "gist/predicate.h"
#include "gist/predicate_holder.h"

template <typename P>
class Entry : public PredicateHolder<P> {
private:
    P *predicate;
    int nsn;
public:
    void setPredicate(P *predicate) {
        this->predicate = predicate;
    }

    virtual std::vector<Entry<P> *> getChildren() = 0;

    P *getPredicate() const {
        return predicate;
    }

    int getNSN() {
    	return nsn;
    }
};