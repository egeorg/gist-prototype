#pragma once

#include "gist/predicate.h"
#include "gist/predicate_holder.h"
#include "gist/shared_mutex.h"

template <typename P>
class Entry : public PredicateHolder<P> {
protected:
    P *predicate;
    Entry<P> *rightEntry;
    int nsn;
public:
    Entry() {
        this->rightEntry = nullptr;
    }

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

    void setNSN(int newNSN) {
        nsn = newNSN;
    }

    Entry<P>* getRightEntry() {
        return rightEntry;
    }

    void setRightEntry(Entry<P> *rightEntry) {
        this->rightEntry = rightEntry;
    }
};
