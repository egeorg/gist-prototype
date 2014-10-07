#ifndef GIST_GIST_GIST_H_
#define GIST_GIST_GIST_H_

#include <vector>

#include "gist/entry.h"
#include "gist/predicate.h"

class Gist {
public:
    Gist();
    ~Gist();
    std::vector<Entry *> *Search(Predicate *p);
    void Insert(Entry *e);
    void Delete(Entry *e);

protected:
    virtual bool Consistent(Entry *e, Predicate *q) = 0;
    virtual Predicate *Union(const std::vector<Entry *> &p) = 0;
    virtual Entry *Compress(Entry *e) = 0;
    virtual Entry *Decompress(Entry *e) = 0;
    virtual double Penalty(Entry *e1, Entry *e2) = 0;
    virtual bool PickSplit(const std::vector<Entry *> &p) = 0;
};

#endif  // GIST_GIST_GIST_H_
