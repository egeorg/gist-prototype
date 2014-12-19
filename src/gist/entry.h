#pragma once

#include "gist/predicate.h"
#include "gist/predicate_holder.h"

template <typename P>
class Entry : public PredicateHolder<P> {
protected:
    P *predicate;
private:
    int nsn;
    Entry<P> *rightEntry;
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

    int setNSN(int newNSN) {
        nsn = newNSN;
    }

    Entry<P>* getRightEntry() {
        return rightEntry;
    }

    void setRightEntry(Entry<P> *rightEntry) {
        this->rightEntry = rightEntry;
    }
};