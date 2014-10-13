#ifndef GIST_GIST_GIST_H_
#define GIST_GIST_GIST_H_

#include <vector>

#include "gist/predicate.h"

class Gist {
    class Entry {
    private:
        Entry* leftChild;
        Entry* rightBrother;
        Predicate predicate;

        Predicate getPredicate() const {
            return predicate;
        }

        void setPredicate(Predicate &p) {
            predicate = p;
        }
    };

public:
    Gist();
    ~Gist();
    std::vector<Entry *> *Search(Predicate *p) const;
    void Insert(Entry *e);
    void Delete(Entry *e);

protected:
    virtual double Penalty(Entry *e1, Entry *e2) const = 0;
    virtual bool PickSplit(const std::vector<Entry *> &p) const = 0;
};

#endif  // GIST_GIST_GIST_H_
