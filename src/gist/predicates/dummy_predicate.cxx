#include "gist/predicates/dummy_predicate.h"

DummyPredicate::DummyPredicate(const std::vector<DummyPredicate *> &p) {
}

DummyPredicate::DummyPredicate(const std::vector<void *> &data) {
}

DummyPredicate::~DummyPredicate() {
}

bool DummyPredicate::consistentWith(const DummyPredicate &p) const {
    return true;
}

double DummyPredicate::penalty(const DummyPredicate &p) {
    return 0.0;
}

std::pair<DummyPredicate::DPVector, DummyPredicate::DPVector> DummyPredicate::pickSplit(const DummyPredicate::DPVector &p) {
    DummyPredicate::DPVector result_0(p.begin(), p.begin() + p.size() / 2);
    DummyPredicate::DPVector result_1(p.begin() + p.size() / 2, p.end());
    return std::pair<DummyPredicate::DPVector, DummyPredicate::DPVector>(result_0, result_1);
}
