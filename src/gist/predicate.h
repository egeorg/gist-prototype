#pragma once

#include "gist/predicate_holder.h"

class Predicate {
public:
    Predicate(const std::vector<Predicate &> &p);
    Predicate(const std::vector<void *> &data);
    Predicate();
    virtual ~Predicate();

protected:
    virtual bool consistentWith(const Predicate &p) const = 0;
    virtual double penalty(const Predicate &p) const = 0;
    static std::pair<std::vector<PredicateHolder<Predicate> &>, std::vector<PredicateHolder<Predicate> &>> pickSplit(const std::vector<PredicateHolder<Predicate> &> &p);
};