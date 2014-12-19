#pragma once

#include <stdint.h>
#include <vector>

#include "gist/predicate_holder.h"


class DummyPredicate {
private:
    typedef std::vector<PredicateHolder<DummyPredicate> *> DPVector;

public:
    DummyPredicate(const std::vector<DummyPredicate *> &p);

    DummyPredicate(const std::vector<void *> &data);

    virtual ~DummyPredicate();

    bool consistentWith(const DummyPredicate &p) const;

    double penalty(const DummyPredicate &p) const;

    static std::pair<DPVector, DPVector> pickSplit(const DPVector &p);
};